#pragma once

#include <string>
#include <vector>

#include "../../database/sqlite/sqlite3.h"

struct Question {
  int questionId;
  std::string topic;
  int gradeLevel;
  std::string questionText;
  int correctAnswer;
  std::string explanation;
};

struct AnsweredQuestion {
  int questionId;
  std::string topic;
  int gradeLevel;
  bool wasCorrect;
};

class QuestionBank {
public:
  QuestionBank(const std::string &pathToDatabase);
  ~QuestionBank();

  bool databaseIsOpen() const;

  std::vector<Question> getRandomQuestions(int numberOfQuestions, int gradeLevel,
                                           const std::string &topic);

  void saveSessionResults(const std::string &sessionId, int gradeLevel, const std::string &topic,
                          const std::vector<AnsweredQuestion> &answeredQuestions);

private:
  sqlite3 *database;

  void createAnalyticsTablesIfMissing();
};