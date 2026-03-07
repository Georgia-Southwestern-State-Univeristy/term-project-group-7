#include <cassert>
#include <string>

#include "../src/in_memory_store.h"
#include "../src/mvp_service.h"

int main() {
  InMemoryStore store;
  MvpService svc(store);

  std::string err;

  auto s = svc.create_student("Alex", 7, err);
  assert(s.has_value());

  auto a = svc.add_assessment_and_recommend(s->studentId, "fractions", 62, err);
  assert(a.has_value());

  auto rec = svc.latest_recommendation(s->studentId, err);
  assert(rec.has_value());
  assert(rec->source == "rules");

  auto ov = svc.teacher_override(s->studentId, "fractions_practice_set_A", "Teacher override", err);
  assert(ov.has_value());
  assert(ov->source == "override");

  auto rec2 = svc.latest_recommendation(s->studentId, err);
  assert(rec2.has_value());
  assert(rec2->source == "override");
  return 0;
}