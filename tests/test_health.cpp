#include <chrono>
#include <httplib.h>
#include <iostream>
#include <thread>

void testAdditionProblem();
void testAdditionProblemGenerator();
void testSubtractionProblem();
void testSubtractionProblemGenerator();
void testMultiplicationProblem();
void testMultiplicationProblemGenerator();

int main() {
  constexpr int kPort = 5000;

  httplib::Server svr;

  // Self-contained health endpoint
  svr.Get("/api/health", [](const httplib::Request &, httplib::Response &res) {
    res.set_content(R"({"status":"ok"})", "application/json");
    res.status = 200;
  });

  // Start server in background
  std::thread t([&]() { svr.listen("127.0.0.1", kPort); });

  // Give it a moment to start
  std::this_thread::sleep_for(std::chrono::milliseconds(150));

  // Call endpoint
  httplib::Client cli("127.0.0.1", kPort);
  auto resp = cli.Get("/api/health");

  // Stop server
  svr.stop();
  if (t.joinable())
    t.join();

  if (!resp) {
    std::cerr << "FAIL: No response from /api/health\n";
    return 1;
  }
  if (resp->status != 200) {
    std::cerr << "FAIL: Expected 200, got " << resp->status << "\n";
    return 1;
  }

  std::cout << "PASS: /api/health OK\n";

  testAdditionProblem();
  testAdditionProblemGenerator();
  testSubtractionProblem();
  testSubtractionProblemGenerator();
  testMultiplicationProblem();
  testMultiplicationProblemGenerator();

  return 0;
}