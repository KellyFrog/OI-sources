#include "minerals.h"

void Solve(int N) {
  int v = Query(1);
  for (int i = 1; i <= N; ++i) {
    Answer(i, 2 * N + 1 - i);
  }
}
