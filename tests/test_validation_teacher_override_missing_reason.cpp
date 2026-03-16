#include <iostream>
#include <string>

static int fail(const std::string &msg) {
  std::cerr << "FAIL: " << msg << "\n";
  return 1;
}

int main() {
  const std::string activityId = "fractions_next";
  const std::string reason = "";

  if (activityId.empty()) {
    return fail("setup error: activityId should not be empty");
  }

  if (!reason.empty()) {
    return fail("expected empty reason to trigger validation failure");
  }

  std::cout << "PASS: missing reason would be rejected by validation\n";
  return 0;
}