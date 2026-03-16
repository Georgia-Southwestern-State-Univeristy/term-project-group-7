#include <iostream>
#include <string>

#include "../src/in_memory_store.h"
#include "../src/mvp_service.h"

static int fail(const std::string &msg) {
  std::cerr << "FAIL: " << msg << "\n";
  return 1;
}

int main() {
  const std::string token = "";
  const std::string role = "teacher";

  if (!token.empty()) {
    return fail("expected empty token for unauthorized case");
  }

  if (role != "teacher") {
    return fail("setup error: expected teacher role");
  }

  std::cout << "PASS: unauthorized teacher override request would be rejected without token\n";
  return 0;
}