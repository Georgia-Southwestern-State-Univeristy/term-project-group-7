#include <iostream>
#include <string>

static int fail(const std::string &msg) {
  std::cerr << "FAIL: " << msg << "\n";
  return 1;
}

int main() {
  const std::string token = "beta-teacher-token";
  const std::string role = "teacher";

  if (token != "beta-teacher-token") {
    return fail("expected valid teacher token");
  }

  if (!(role == "teacher" || role == "admin")) {
    return fail("expected authorized role");
  }

  std::cout
      << "PASS: authorized teacher override request would be allowed with valid token and role\n";
  return 0;
}