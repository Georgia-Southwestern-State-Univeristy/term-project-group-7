#include "gui/question_bank.h"
#include "../../database/sqlite/sqlite3.h"

#include <ctime>
#include <stdexcept>

QuestionBank::QuestionBank(const std::string &pathToDatabase) : database(nullptr) {
  int openResult = sqlite3_open(pathToDatabase.c_str(), &database);

  if (openResult != SQLITE_OK) {
    std::string errorMessage = database ? sqlite3_errmsg(database) : "unknown error";
    sqlite3_close(database);
    database = nullptr;
    throw std::runtime_error("Could not open the database at " + pathToDatabase + ": " +
                             errorMessage);
  }

  createAnalyticsTablesIfMissing();
}

QuestionBank::~QuestionBank() {
  if (database) {
    sqlite3_close(database);
    database = nullptr;
  }
}

bool QuestionBank::databaseIsOpen() const { return database != nullptr; }

void QuestionBank::createAnalyticsTablesIfMissing() {
  if (!database)
    return;

  const char *createTablesSQL = "CREATE TABLE IF NOT EXISTS sessions ("
                                "    session_id       TEXT PRIMARY KEY,"
                                "    started_at       INTEGER NOT NULL,"
                                "    grade_level      INTEGER NOT NULL,"
                                "    topic            TEXT NOT NULL,"
                                "    total_questions  INTEGER NOT NULL,"
                                "    correct_answers  INTEGER NOT NULL,"
                                "    score_percentage REAL NOT NULL"
                                ");"
                                "CREATE TABLE IF NOT EXISTS session_answers ("
                                "    id           INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "    session_id   TEXT NOT NULL REFERENCES sessions(session_id),"
                                "    question_id  INTEGER NOT NULL,"
                                "    topic        TEXT NOT NULL,"
                                "    grade_level  INTEGER NOT NULL,"
                                "    was_correct  INTEGER NOT NULL"
                                ");";

  char *errorMessage = nullptr;
  sqlite3_exec(database, createTablesSQL, nullptr, nullptr, &errorMessage);
  if (errorMessage)
    sqlite3_free(errorMessage);
}

std::vector<Question> QuestionBank::getRandomQuestions(int numberOfQuestions, int gradeLevel,
                                                       const std::string &topic) {
  std::vector<Question> questions;

  if (!database)
    return questions;

  const char *querySQL =
      "SELECT id, topic, grade_level, question_text, correct_answer, explanation "
      "FROM questions "
      "WHERE grade_level = ? AND LOWER(topic) = LOWER(?) "
      "ORDER BY RANDOM() LIMIT ?;";

  sqlite3_stmt *preparedStatement = nullptr;
  if (sqlite3_prepare_v2(database, querySQL, -1, &preparedStatement, nullptr) != SQLITE_OK)
    return questions;

  sqlite3_bind_int(preparedStatement, 1, gradeLevel);
  sqlite3_bind_text(preparedStatement, 2, topic.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_int(preparedStatement, 3, numberOfQuestions);

  while (sqlite3_step(preparedStatement) == SQLITE_ROW) {
    Question question;

    question.questionId = sqlite3_column_int(preparedStatement, 0);

    const char *topicText =
        reinterpret_cast<const char *>(sqlite3_column_text(preparedStatement, 1));
    question.topic = topicText ? topicText : "";

    question.gradeLevel = sqlite3_column_int(preparedStatement, 2);

    const char *questionText =
        reinterpret_cast<const char *>(sqlite3_column_text(preparedStatement, 3));
    question.questionText = questionText ? questionText : "";

    question.correctAnswer = sqlite3_column_int(preparedStatement, 4);

    const char *explanationText =
        reinterpret_cast<const char *>(sqlite3_column_text(preparedStatement, 5));
    question.explanation = explanationText ? explanationText : "";

    questions.push_back(question);
  }

  sqlite3_finalize(preparedStatement);
  return questions;
}

void QuestionBank::saveSessionResults(const std::string &sessionId, int gradeLevel,
                                      const std::string &topic,
                                      const std::vector<AnsweredQuestion> &answeredQuestions) {
  if (!database || answeredQuestions.empty())
    return;

  int totalQuestions = static_cast<int>(answeredQuestions.size());
  int correctAnswers = 0;

  for (const auto &answeredQuestion : answeredQuestions) {
    if (answeredQuestion.wasCorrect) {
      correctAnswers++;
    }
  }

  double scorePercentage = totalQuestions > 0 ? (correctAnswers * 100.0 / totalQuestions) : 0.0;
  long long timeSessionStarted = static_cast<long long>(time(nullptr));

  sqlite3_exec(database, "BEGIN;", nullptr, nullptr, nullptr);

  const char *upsertSessionSQL = "INSERT INTO sessions "
                                 "(session_id, started_at, grade_level, topic, total_questions, "
                                 " correct_answers, score_percentage) "
                                 "VALUES (?, ?, ?, ?, ?, ?, ?) "
                                 "ON CONFLICT(session_id) DO UPDATE SET "
                                 "  started_at = excluded.started_at, "
                                 "  grade_level = excluded.grade_level, "
                                 "  topic = excluded.topic, "
                                 "  total_questions = excluded.total_questions, "
                                 "  correct_answers = excluded.correct_answers, "
                                 "  score_percentage = excluded.score_percentage;";

  sqlite3_stmt *preparedStatement = nullptr;
  if (sqlite3_prepare_v2(database, upsertSessionSQL, -1, &preparedStatement, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_text(preparedStatement, 1, sessionId.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(preparedStatement, 2, timeSessionStarted);
    sqlite3_bind_int(preparedStatement, 3, gradeLevel);
    sqlite3_bind_text(preparedStatement, 4, topic.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(preparedStatement, 5, totalQuestions);
    sqlite3_bind_int(preparedStatement, 6, correctAnswers);
    sqlite3_bind_double(preparedStatement, 7, scorePercentage);
    sqlite3_step(preparedStatement);
    sqlite3_finalize(preparedStatement);
  }

  const char *deleteOldAnswersSQL = "DELETE FROM session_answers WHERE session_id = ?;";
  if (sqlite3_prepare_v2(database, deleteOldAnswersSQL, -1, &preparedStatement, nullptr) ==
      SQLITE_OK) {
    sqlite3_bind_text(preparedStatement, 1, sessionId.c_str(), -1, SQLITE_STATIC);
    sqlite3_step(preparedStatement);
    sqlite3_finalize(preparedStatement);
  }

  const char *insertAnswerSQL = "INSERT INTO session_answers "
                                "(session_id, question_id, topic, grade_level, was_correct) "
                                "VALUES (?, ?, ?, ?, ?);";

  for (const auto &answeredQuestion : answeredQuestions) {
    if (sqlite3_prepare_v2(database, insertAnswerSQL, -1, &preparedStatement, nullptr) ==
        SQLITE_OK) {
      sqlite3_bind_text(preparedStatement, 1, sessionId.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_int(preparedStatement, 2, answeredQuestion.questionId);
      sqlite3_bind_text(preparedStatement, 3, answeredQuestion.topic.c_str(), -1, SQLITE_STATIC);
      sqlite3_bind_int(preparedStatement, 4, answeredQuestion.gradeLevel);
      sqlite3_bind_int(preparedStatement, 5, answeredQuestion.wasCorrect ? 1 : 0);
      sqlite3_step(preparedStatement);
      sqlite3_finalize(preparedStatement);
    }
  }

  sqlite3_exec(database, "COMMIT;", nullptr, nullptr, nullptr);
}