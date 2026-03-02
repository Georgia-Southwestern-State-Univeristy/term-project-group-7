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

  // Happy path: gradeLevel boundary min (6) should succeed
  auto s1 = svc.create_student("David", 6, err);
  if (!s1.has_value())
    return fail("gradeLevel 6 should succeed, got: " + err);

  // Happy path: gradeLevel boundary max (8) should succeed
  auto s2 = svc.create_student("Jordan", 8, err);
  if (!s2.has_value())
    return fail("gradeLevel 8 should succeed, got: " + err);

  std::cout << "PASS: gradeLevel boundaries 6 and 8 accepted\n";
  return 0;
}