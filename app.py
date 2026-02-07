from __future__ import annotations

import os
import sqlite3
from datetime import datetime, timezone
from flask import Flask, jsonify, send_from_directory

APP_DIR = os.path.dirname(os.path.abspath(__file__))
DB_PATH = os.path.join(APP_DIR, "app.db")

app = Flask(__name__, static_folder="static")


def get_db() -> sqlite3.Connection:
    conn = sqlite3.connect(DB_PATH)
    conn.execute("PRAGMA journal_mode=WAL;")
    return conn


def init_db() -> None:
    with get_db() as conn:
        conn.execute(
            """
            CREATE TABLE IF NOT EXISTS health_checks (
              id INTEGER PRIMARY KEY AUTOINCREMENT,
              checked_at TEXT NOT NULL
            )
            """
        )
        now = datetime.now(timezone.utc).isoformat()
        conn.execute("INSERT INTO health_checks (checked_at) VALUES (?)", (now,))


@app.get("/api/health")
def health():
    init_db()
    with get_db() as conn:
        row = conn.execute("SELECT COUNT(*) FROM health_checks").fetchone()
        count = int(row[0]) if row else 0

    return jsonify({"status": "ok", "db": "sqlite", "health_checks_count": count})


@app.get("/")
def index():
    return send_from_directory("static", "index.html")


if __name__ == "__main__":
    app.run(host="127.0.0.1", port=5000, debug=True)