#include <iostream>
#include <string>

#include "../src/in_memory_store.h"
#include "../src/mvp_service.h"

static int fail(const std::string &msg) {
  std::cerr << "FAIL: " << msg << "\n";
  return 1;
}

int main() {
  InMemoryStore store;
  MvpService svc(store);
  std::string err;

  auto s = svc.create_student("David", 7, err);
  if (!s.has_value())
    return fail("create_student failed: " + err);

  // Happy path: score 70+ should produce "<skill>_next"
  auto a = svc.add_assessment_and_recommend(s->studentId, "fractions", 90, err);
  if (!a.has_value())
    return fail("add_assessment_and_recommend failed: " + err);

  auto rec = svc.latest_recommendation(s->studentId, err);
  if (!rec.has_value())
    return fail("latest_recommendation failed: " + err);

  if (rec->source != "rules")
    return fail("expected source == rules");
  if (rec->activityId != "fractions_next")
    return fail("expected activityId == fractions_next");

  std::cout << "PASS: high score produces rules recommendation fractions_next\n";
  return 0;
}