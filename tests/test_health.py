from app import app


def test_health_endpoint_returns_ok():
    client = app.test_client()
    res = client.get("/api/health")
    assert res.status_code == 200
    data = res.get_json()
    assert data["status"] == "ok"
    assert data["db"] == "sqlite"
    assert isinstance(data["health_checks_count"], int)