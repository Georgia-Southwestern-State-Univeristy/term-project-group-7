#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "mvp_models.h"

class InMemoryStore {
public:
  Student create_student(const std::string &name, int gradeLevel) {
    Student s;
    s.studentId = next_id("stu_");
    s.name = name;
    s.gradeLevel = gradeLevel;
    students_[s.studentId] = s;
    return s;
  }

  std::optional<Student> get_student(const std::string &studentId) const {
    auto it = students_.find(studentId);
    if (it == students_.end())
      return std::nullopt;
    return it->second;
  }

  Assessment add_assessment(const std::string &studentId, const std::string &skill, int score) {
    Assessment a;
    a.assessmentId = next_id("asm_");
    a.studentId = studentId;
    a.skill = skill;
    a.score = score;
    assessments_by_student_[studentId].push_back(a);
    return a;
  }

  Recommendation set_latest_recommendation(const Recommendation &rec) {
    latest_rec_by_student_[rec.studentId] = rec;
    return rec;
  }

  std::optional<Recommendation> get_latest_recommendation(const std::string &studentId) const {
    auto it = latest_rec_by_student_.find(studentId);
    if (it == latest_rec_by_student_.end())
      return std::nullopt;
    return it->second;
  }

private:
  std::string next_id(const std::string &prefix) {
    ++counter_;
    return prefix + std::to_string(counter_);
  }

  int counter_{0};
  std::unordered_map<std::string, Student> students_;
  std::unordered_map<std::string, std::vector<Assessment>> assessments_by_student_;
  std::unordered_map<std::string, Recommendation> latest_rec_by_student_;
};