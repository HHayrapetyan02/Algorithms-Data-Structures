#include <iostream>
#include <vector>
#include <numeric>

int32_t FindSet(int32_t x, std::vector<int32_t>& parent) {
  if (x == parent[x]) {
    return x;
  }
  return parent[x] = FindSet(parent[x], parent);
}

void Union(int32_t x, int32_t y, std::vector<int32_t>& parent, std::vector<int32_t>& rank,
           std::vector<int32_t>& weights, int32_t weight) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (x == y) {
    weights[x] += weight;
  } else {
    if (rank[x] < rank[y]) {
      parent[x] = y;
      weights[y] += weights[x] + weight;
    } else if (rank[x] > rank[y]) {
      parent[y] = x;
      weights[x] += weights[y] + weight;
    } else {
      parent[x] = y;
      weights[y] += weights[x] + weight;
      ++rank[y];
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  std::vector<int32_t> parent(n + 1);
  std::vector<int32_t> rank(n + 1, 1);
  std::vector<int32_t> weights(n + 1, 0);

  std::iota(parent.begin(), parent.end(), 0);
  for (int32_t i = 0; i < m; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      int32_t begin = 0;
      int32_t end = 0;
      int32_t weight = 0;
      std::cin >> begin >> end >> weight;
      Union(begin, end, parent, rank, weights, weight);
    } else if (command == 2) {
      int32_t start = 0;
      std::cin >> start;
      int32_t root = FindSet(start, parent);
      std::cout << weights[root] << "\n";
    }
  }
  return 0;
}
