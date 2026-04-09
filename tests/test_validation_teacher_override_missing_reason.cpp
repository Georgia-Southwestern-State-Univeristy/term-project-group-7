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

  auto student = svc.create_student("Alex", 7, err);
  if (!student.has_value()) {
    return fail("create_student failed: " + err);
  }

  auto rec = svc.teacher_override(student->studentId, "fractions_next", "", err);
  if (rec.has_value()) {
    return fail("expected teacher override with missing reason to fail");
  }

  if (err != "reason is required") {
    return fail("expected err 'reason is required', got: " + err);
  }

  std::cout << "PASS: missing teacher override reason rejected by service validation\n";
  return 0;
}