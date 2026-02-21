#pragma once
#include <string>

struct Student {
  std::string studentId;
  std::string name;
  int gradeLevel{};
};

struct Assessment {
  std::string assessmentId;
  std::string studentId;
  std::string skill;
  int score{};
};

struct Recommendation {
  std::string recommendationId;
  std::string studentId;
  std::string activityId;
  std::string reason;
  std::string source; // "rules" or "override"
};