#include <iostream>
#include <optional>
#include <string>

#include "httplib.h"
#include "menu/menu.h"

#include "in_memory_store.h"
#include "mvp_service.h"

static const char *INDEX_HTML = R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Thin Vertical Slice</title>
</head>
<body>
  <h1>OK - App is running</h1>
  <p>Health endpoint: <code>/api/health</code></p>
</body>
</html>
)HTML";

static std::optional<std::string> json_get_string(const std::string &body, const std::string &key) {
  // Very small parser: expects "key":"value"
  const std::string pat = "\"" + key + "\"";
  auto kpos = body.find(pat);
  if (kpos == std::string::npos)
    return std::nullopt;
  auto colon = body.find(":", kpos);
  if (colon == std::string::npos)
    return std::nullopt;
  auto q1 = body.find("\"", colon);
  if (q1 == std::string::npos)
    return std::nullopt;
  auto q2 = body.find("\"", q1 + 1);
  if (q2 == std::string::npos)
    return std::nullopt;
  return body.substr(q1 + 1, q2 - (q1 + 1));
}

static std::optional<int> json_get_int(const std::string &body, const std::string &key) {
  // Expects "key": 123
  const std::string pat = "\"" + key + "\"";
  auto kpos = body.find(pat);
  if (kpos == std::string::npos)
    return std::nullopt;
  auto colon = body.find(":", kpos);
  if (colon == std::string::npos)
    return std::nullopt;
  auto start = body.find_first_of("-0123456789", colon);
  if (start == std::string::npos)
    return std::nullopt;
  auto end = body.find_first_not_of("0123456789", start);
  auto num = body.substr(start, end - start);
  try {
    return std::stoi(num);
  } catch (...) {
    return std::nullopt;
  }
}

static void json_error(httplib::Response &res, int code, const std::string &msg) {
  res.status = code;
  res.set_content(std::string("{\"error\":\"") + msg + "\"}", "application/json; charset=utf-8");
}

int main() {
  runMainMenu();

  httplib::Server server;

  InMemoryStore store;
  MvpService svc(store);

  server.Get("/", [](const httplib::Request &, httplib::Response &res) {
    res.set_content(INDEX_HTML, "text/html; charset=utf-8");
  });

  server.Get("/api/health", [](const httplib::Request &, httplib::Response &res) {
    res.set_content(R"({"status":"ok","service":"cpp"})", "application/json; charset=utf-8");
  });

  server.Post("/api/students", [&](const httplib::Request &req, httplib::Response &res) {
    auto name = json_get_string(req.body, "name");
    auto grade = json_get_int(req.body, "gradeLevel");
    if (!name.has_value() || !grade.has_value()) {
      return json_error(res, 400, "name and gradeLevel are required");
    }

    std::string err;
    auto s = svc.create_student(*name, *grade, err);
    if (!s.has_value()) {
      return json_error(res, 400, err);
    }

    res.status = 201;
    res.set_content(std::string("{\"studentId\":\"") + s->studentId + "\",\"name\":\"" + s->name +
                        "\",\"gradeLevel\":" + std::to_string(s->gradeLevel) + "}",
                    "application/json; charset=utf-8");
  });

  server.Post(R"(/api/students/([A-Za-z0-9_]+)/assessments)",
              [&](const httplib::Request &req, httplib::Response &res) {
                const std::string studentId = req.matches[1];

                auto skill = json_get_string(req.body, "skill");
                auto score = json_get_int(req.body, "score");
                if (!skill.has_value() || !score.has_value()) {
                  return json_error(res, 400, "skill and score are required");
                }

                std::string err;
                auto a = svc.add_assessment_and_recommend(studentId, *skill, *score, err);
                if (!a.has_value()) {
                  if (err == "student not found")
                    return json_error(res, 404, err);
                  return json_error(res, 400, err);
                }

                res.status = 201;
                res.set_content(std::string("{\"assessmentId\":\"") + a->assessmentId +
                                    "\",\"studentId\":\"" + a->studentId + "\",\"skill\":\"" +
                                    a->skill + "\",\"score\":" + std::to_string(a->score) + "}",
                                "application/json; charset=utf-8");
              });

  server.Get(R"(/api/students/([A-Za-z0-9_]+)/recommendations/latest)",
             [&](const httplib::Request &req, httplib::Response &res) {
               const std::string studentId = req.matches[1];

               std::string err;
               auto rec = svc.latest_recommendation(studentId, err);
               if (!rec.has_value()) {
                 return json_error(res, 404, err);
               }

               res.status = 200;
               res.set_content(std::string("{\"recommendationId\":\"") + rec->recommendationId +
                                   "\",\"studentId\":\"" + rec->studentId + "\",\"activityId\":\"" +
                                   rec->activityId + "\",\"reason\":\"" + rec->reason +
                                   "\",\"source\":\"" + rec->source + "\"}",
                               "application/json; charset=utf-8");
             });

  server.Post(R"(/api/students/([A-Za-z0-9_]+)/teacher-override)",
              [&](const httplib::Request &req, httplib::Response &res) {
                const std::string studentId = req.matches[1];

                auto activityId = json_get_string(req.body, "activityId");
                auto reason = json_get_string(req.body, "reason");
                if (!activityId.has_value() || !reason.has_value()) {
                  return json_error(res, 400, "activityId and reason are required");
                }

                std::string err;
                auto rec = svc.teacher_override(studentId, *activityId, *reason, err);
                if (!rec.has_value()) {
                  return json_error(res, 404, err);
                }

                res.status = 200;
                res.set_content(std::string("{\"recommendationId\":\"") + rec->recommendationId +
                                    "\",\"studentId\":\"" + rec->studentId +
                                    "\",\"activityId\":\"" + rec->activityId + "\",\"reason\":\"" +
                                    rec->reason + "\",\"source\":\"" + rec->source + "\"}",
                                "application/json; charset=utf-8");
              });

  std::cout << "Running on http://127.0.0.1:5000\n";


  server.listen("127.0.0.1", 5000);
  return 0;
}