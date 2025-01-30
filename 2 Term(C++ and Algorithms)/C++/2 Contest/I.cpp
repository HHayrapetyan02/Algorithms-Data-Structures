#include <iostream>
#include <queue>
#include <vector>

int main() {
  int n = 0;
  std::cin >> n;
  std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
  for (int i = 0; i < n; ++i) {
    int num = 0;
    std::cin >> num;
    queue.push(num);
  }
  long double ans = 0;
  while (queue.size() > 1) {
    int res = 0;
    res += queue.top();
    queue.pop();
    res += queue.top();
    queue.pop();
    queue.push(res);
    ans += res;
  }
  std::cout << ans * 0.05 << "\n";
  return 0;
}
