#include <iostream>
#include <string>

#include "httplib.h"

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

int main() {
  httplib::Server server;

  server.Get("/", [](const httplib::Request &, httplib::Response &res) {
    res.set_content(INDEX_HTML, "text/html; charset=utf-8");
  });

  server.Get("/api/health", [](const httplib::Request &, httplib::Response &res) {
    res.set_content(R"({"status":"ok","service":"cpp"})", "application/json; charset=utf-8");
  });

  std::cout << "Running on http://127.0.0.1:5000\n";
  server.listen("127.0.0.1", 5000);
  return 0;
}