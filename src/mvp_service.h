#pragma once
#include <optional>
#include <string>

#include "in_memory_store.h"

class MvpService {
public:
  explicit MvpService(InMemoryStore &store) : store_(store) {}

  std::optional<Student> create_student(const std::string &name, int gradeLevel, std::string &err) {
    if (name.empty()) {
      err = "name is required";
      return std::nullopt;
    }
    if (gradeLevel < 6 || gradeLevel > 8) {
      err = "gradeLevel must be between 6 and 8 for MVP";
      return std::nullopt;
    }
    err.clear();
    return store_.create_student(name, gradeLevel);
  }

  std::optional<Assessment> add_assessment_and_recommend(const std::string &studentId,
                                                         const std::string &skill, int score,
                                                         std::string &err) {
    auto student = store_.get_student(studentId);
    if (!student.has_value()) {
      err = "student not found";
      return std::nullopt;
    }
    if (skill.empty()) {
      err = "skill is required";
      return std::nullopt;
    }
    if (score < 0 || score > 100) {
      err = "score must be 0..100";
      return std::nullopt;
    }

    err.clear();
    auto a = store_.add_assessment(studentId, skill, score);
    auto rec = make_rule_recommendation(studentId, skill, score);
    store_.set_latest_recommendation(rec);
    return a;
  }

  std::optional<Recommendation> latest_recommendation(const std::string &studentId,
                                                      std::string &err) {
    auto student = store_.get_student(studentId);
    if (!student.has_value()) {
      err = "student not found";
      return std::nullopt;
    }
    auto rec = store_.get_latest_recommendation(studentId);
    if (!rec.has_value()) {
      err = "no recommendation yet";
      return std::nullopt;
    }
    err.clear();
    return rec;
  }

  std::optional<Recommendation> teacher_override(const std::string &studentId,
                                                 const std::string &activityId,
                                                 const std::string &reason, std::string &err) {
    auto student = store_.get_student(studentId);
    if (!student.has_value()) {
      err = "student not found";
      return std::nullopt;
    }
    if (activityId.empty()) {
      err = "activityId is required";
      return std::nullopt;
    }
    if (reason.empty()) {
      err = "reason is required";
      return std::nullopt;
    }

    Recommendation rec;
    rec.recommendationId = "rec_override";
    rec.studentId = studentId;
    rec.activityId = activityId;
    rec.reason = reason;
    rec.source = "override";

    err.clear();
    return store_.set_latest_recommendation(rec);
  }

private:
  Recommendation make_rule_recommendation(const std::string &studentId, const std::string &skill,
                                          int score) {
    Recommendation rec;
    rec.recommendationId = "rec_rules";
    rec.studentId = studentId;
    rec.source = "rules";

    if (score < 70) {
      rec.activityId = skill + "_foundations";
      rec.reason = "Score below 70 → reinforce foundations.";
    } else {
      rec.activityId = skill + "_next";
      rec.reason = "Score 70+ → advance to next activity.";
    }
    return rec;
  }

  InMemoryStore &store_;
};