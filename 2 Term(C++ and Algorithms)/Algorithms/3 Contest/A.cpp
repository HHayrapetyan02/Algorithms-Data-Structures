#include <iostream>
#include <vector>
#include <numeric>

int32_t FindSet(int32_t x, std::vector<int32_t>& parent) {
  if (x == parent[x]) {
    return x;
  }
  return parent[x] = FindSet(parent[x], parent);
}

void Union(int32_t x, int32_t y, std::vector<int32_t>& parent, std::vector<int32_t>& rank) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (rank[x] < rank[y]) {
    parent[x] = y;
  } else if (rank[x] > rank[y]) {
    parent[y] = x;
  } else {
    parent[x] = y;
    ++rank[y];
  }
}

int32_t MinIsland(int32_t n, int32_t m, std::vector<int32_t>& parent, std::vector<int32_t>& rank) {
  for (int32_t i = 0; i < m; ++i) {
    int32_t begin = 0;
    int32_t end = 0;
    std::cin >> begin >> end;
    if (FindSet(begin, parent) != FindSet(end, parent)) {
      Union(begin, end, parent, rank);
      --n;
      if (n == 1) {
        return i + 1;
      }
    }
  }
  return m;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  std::vector<int32_t> parent(n);
  std::vector<int32_t> rank(n, 1);
  std::iota(parent.begin(), parent.end(), 0);
  std::cout << MinIsland(n, m, parent, rank) << "\n";
  return 0;
}
