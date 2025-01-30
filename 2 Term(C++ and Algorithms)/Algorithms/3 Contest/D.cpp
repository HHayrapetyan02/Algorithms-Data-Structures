#include <iostream>
#include <vector>
#include <numeric>

struct Edge {
  int32_t begin = 0;
  int32_t end = 0;
  size_t weight = 0;
  Edge() = default;
  Edge(const int32_t& begin, const int32_t& end, const size_t& weight) : begin(begin), end(end), weight(weight) {
  }
};

int32_t FindSet(int32_t x, std::vector<int32_t>& parent) {
  if (x == parent[x]) {
    return x;
  }
  return parent[x] = FindSet(parent[x], parent);
}

void Union(int32_t x, int32_t y, std::vector<int32_t>& parent, std::vector<int32_t>& rank) {
  x = FindSet(x, parent);
  y = FindSet(y, parent);
  if (rank[x] > rank[y]) {
    parent[y] = x;
  } else if (rank[x] < rank[y]) {
    parent[x] = y;
  } else {
    parent[x] = y;
    ++rank[y];
  }
}

size_t Kruskal(int32_t m, std::vector<int32_t>& parent, std::vector<int32_t>& rank, std::vector<Edge>& edges) {
  for (int32_t i = 0; i < m; ++i) {
    int32_t begin = 0;
    int32_t end = 0;
    size_t weight = 0;
    std::cin >> begin >> end >> weight;
    Edge rebro(begin, end, weight);
    edges[i] = rebro;
  }
  size_t weight = 0;
  for (int32_t i = 0; i < m; ++i) {
    if (FindSet(edges[i].begin, parent) != FindSet(edges[i].end, parent)) {
      Union(edges[i].begin, edges[i].end, parent, rank);
      weight += edges[i].weight;
    }
  }
  return weight;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  std::vector<int32_t> parent(n + 1);
  std::vector<int32_t> rank(n + 1, 1);
  std::vector<Edge> edges(m + 1);
  std::iota(parent.begin(), parent.end(), 0);
  std::cout << Kruskal(m, parent, rank, edges) << "\n";
  return 0;
}
