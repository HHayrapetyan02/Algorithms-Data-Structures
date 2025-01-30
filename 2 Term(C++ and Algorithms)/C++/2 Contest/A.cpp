#include <iostream>
#include <vector>
#include <algorithm>

struct Command {
  int tasks = 0;
  int time = 0;
  int number = 0;
  Command() : tasks(0), time(0), number(0) {
  }
  Command(const int& tasks, const int& time) : tasks(tasks), time(time) {
  }
};

bool Comparator(Command first, Command second) {
  if (first.tasks > second.tasks) {
    return true;
  }
  if (first.tasks == second.tasks) {
    if (first.time < second.time) {
      return true;
    }
    if (first.time == second.time) {
      return first.number < second.number;
    }
    return false;
  }
  return false;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Command> table(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> table[i].tasks >> table[i].time;
    table[i].number = i + 1;
  }
  std::sort(table.begin(), table.end(), Comparator);
  for (const auto& elem : table) {
    std::cout << elem.number << "\n";
  }
  return 0;
}
