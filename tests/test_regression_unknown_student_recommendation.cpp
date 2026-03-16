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

  auto rec = svc.latest_recommendation("missing_student", err);
  if (rec.has_value()) {
    return fail("expected missing student recommendation lookup to fail");
  }

  if (err != "student not found") {
    return fail("expected 'student not found', got: " + err);
  }

  std::cout << "PASS: regression check for unknown student recommendation lookup\n";
  return 0;
}