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

  auto student = svc.create_student("Maya", 6, err);
  if (!student.has_value()) {
    return fail("create_student failed: " + err);
  }

  auto assessment = svc.add_assessment_and_recommend(student->studentId, "", 55, err);
  if (assessment.has_value()) {
    return fail("expected missing skill to fail");
  }

  if (err != "skill is required") {
    return fail("expected err 'skill is required', got: " + err);
  }

  std::cout << "PASS: refactored assessment validation rejects missing skill\n";
  return 0;
}