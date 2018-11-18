#include <queue>
#include "simple.hh"

int main() {
  deque<pair<int,int>> tasks;
  ull x = 9;
  bool doing_task = false;
  int task_counter = 8, delay = 0;
  for (ull t = 1; ; ++t) {
    printf("t=%d, tasks.size()=%d\n", t, tasks.size());

    if (t >= 1)
      if ((t == 1) || (((t - 1) % 42) == 0))
        tasks.push_back({ 1, 14 });
    if (t >= 3)
      if ((t == 3) || (((t - 1) % x) == 0))
        tasks.push_back({ 2, 5 });

    if (delay) {
      --delay;
      continue;
    }

    if (!tasks.empty()) {
      if (task_counter != 0) {
        if (tasks[0].second == 1) {
          tasks.pop_front();
          task_counter = 8;
        } else {
          --task_counter;
          --tasks[0].second;
        }
      } else {
        pair<int,int> v = tasks[0];
        tasks.pop_front();
        tasks.push_back(v);
        if (tasks.front().first != v.first)
          delay = 3;
        task_counter = 8;
      }
    }
  }
}

