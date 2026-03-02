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

  // Failure path: score outside 0..100 must fail with validation error
  auto a = svc.add_assessment_and_recommend(s->studentId, "fractions", 101, err);
  if (a.has_value())
    return fail("expected invalid score to fail, but it succeeded");

  if (err != "score must be 0..100")
    return fail("expected err 'score must be 0..100', got: " + err);

  std::cout << "PASS: invalid score rejected with correct error\n";
  return 0;
}