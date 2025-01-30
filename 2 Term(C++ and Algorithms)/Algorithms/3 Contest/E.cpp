#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <queue>

const auto kInf = std::numeric_limits<int32_t>::max();

struct Edge {
  int32_t begin = 0;
  int32_t end = 0;
  size_t weight = 0;
  Edge() = default;
  Edge(const int32_t& begin, const int32_t& end, const size_t& weight) : begin(begin), end(end), weight(weight) {
  }
  bool operator>(const Edge& other) const {
    return weight > other.weight;
  }
};

int32_t FindSet(int32_t x, std::vector<int32_t>& parent) {
  if (x == parent[x]) {
    return x;
  }
  return parent[x] = FindSet(parent[x], parent);
}

void Union(int32_t x, int32_t y, std::vector<int32_t>& parent, std::vector<int32_t>& rank, int32_t& set_count) {
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
  --set_count;
}

size_t Boruvka(std::vector<int32_t>& parent, std::vector<int32_t>& rank, std::vector<Edge>& edges) {
  size_t min_weight = 0;
  auto set_count = static_cast<int32_t>(rank.size() - 1);
  while (set_count > 1) {
    std::vector<Edge> min_edges(parent.size(), {0, 0, kInf});
    for (const auto& rebro : edges) {
      int32_t component_begin = FindSet(rebro.begin, parent);
      int32_t component_end = FindSet(rebro.end, parent);
      if (component_begin != component_end) {
        if (rebro.weight < min_edges[component_begin].weight) {
          min_edges[component_begin] = {rebro.begin, rebro.end, rebro.weight};
        }
        if (rebro.weight < min_edges[component_end].weight) {
          min_edges[component_end] = {rebro.begin, rebro.end, rebro.weight};
        }
      }
    }
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
    for (const auto& rebro : min_edges) {
      if (rebro.begin != 0) {
        queue.emplace(rebro);
      }
    }
    while (!queue.empty()) {
      Edge rebro = queue.top();
      queue.pop();
      int32_t component_begin = FindSet(rebro.begin, parent);
      int32_t component_end = FindSet(rebro.end, parent);
      if (component_begin != component_end) {
        Union(component_begin, component_end, parent, rank, set_count);
        min_weight += rebro.weight;
        if (set_count <= 1) {
          break;
        }
      }
    }
  }
  return min_weight;
}

std::istream& operator>>(std::istream& io, std::vector<Edge>& edges) {
  for (size_t i = 0; i < edges.size(); ++i) {
    int32_t begin = 0;
    int32_t end = 0;
    size_t weight = 0;
    io >> begin >> end >> weight;
    edges[i] = {begin, end, weight};
  }
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  std::vector<int32_t> parent(n + 1);
  std::iota(parent.begin(), parent.end(), 0);
  std::vector<int32_t> rank(n + 1, 1);
  std::vector<Edge> edges(m);
  std::cin >> edges;
  std::cout << Boruvka(parent, rank, edges) << "\n";
  return 0;
}
