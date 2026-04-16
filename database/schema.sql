DROP TABLE IF EXISTS questions;
DROP TABLE IF EXISTS sessions;
DROP TABLE IF EXISTS session_answers;

CREATE TABLE questions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    topic TEXT NOT NULL CHECK (topic IN ('addition', 'subtraction', 'multiplication', 'division')),
    grade_level INTEGER NOT NULL CHECK (grade_level IN (6, 7, 8)),
    difficulty TEXT NOT NULL DEFAULT 'medium' CHECK (difficulty IN ('easy', 'medium', 'hard')),
    question_text TEXT NOT NULL,
    correct_answer INTEGER NOT NULL,
    explanation TEXT
);

CREATE TABLE sessions (
    session_id TEXT PRIMARY KEY,
    started_at INTEGER NOT NULL,
    grade_level INTEGER NOT NULL,
    topic TEXT NOT NULL,
    total_questions INTEGER NOT NULL,
    correct_answers INTEGER NOT NULL,
    score_percentage REAL NOT NULL
);

CREATE TABLE session_answers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    session_id TEXT NOT NULL,
    question_id INTEGER NOT NULL,
    topic TEXT NOT NULL,
    grade_level INTEGER NOT NULL,
    was_correct INTEGER NOT NULL CHECK (was_correct IN (0,1)),
    FOREIGN KEY (session_id) REFERENCES sessions(session_id),
    FOREIGN KEY (question_id) REFERENCES questions(id)
);