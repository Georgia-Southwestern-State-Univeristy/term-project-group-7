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
  if (!s.has_value()) return fail("create_student failed: " + err);

  // Boundary test: score 70 is the cutoff (score < 70 => foundations, else => next)
  auto a = svc.add_assessment_and_recommend(s->studentId, "fractions", 70, err);
  if (!a.has_value()) return fail("add_assessment_and_recommend failed: " + err);

  auto rec = svc.latest_recommendation(s->studentId, err);
  if (!rec.has_value()) return fail("latest_recommendation failed: " + err);

  if (rec->activityId != "fractions_next") return fail("expected score 70 to produce fractions_next");
  if (rec->source != "rules") return fail("expected source == rules");

  std::cout << "PASS: boundary score 70 produces rules recommendation fractions_next\n";
  return 0;
}