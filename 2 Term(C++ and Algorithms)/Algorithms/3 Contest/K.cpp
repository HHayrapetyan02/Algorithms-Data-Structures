#include <iostream>
#include <vector>
#include <queue>

const auto kConst = 100'000;
const auto kMax = 1'000'000'000;

struct Edge {
  int32_t begin = 0;
  int32_t end = 0;
  int32_t weight = 0;
  Edge() = default;
  Edge(const int32_t& begin, const int32_t& end, const int32_t& weight) : begin(begin), end(end), weight(weight) {
  }
};

struct Graph {
  int32_t n = 0;
  std::vector<Edge> edges;
  Graph() = default;
  explicit Graph(const int32_t& n) : n(n) {
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

bool Relax(const Edge& edge, std::vector<int64_t>& dist, std::vector<int32_t>& cycle) {
  if (dist[edge.end] > dist[edge.begin] + edge.weight) {
    dist[edge.end] = dist[edge.begin] + edge.weight;
    cycle[edge.end] = edge.begin;
    return true;
  }
  return false;
}

void FormReversedCorrectCycle(const std::vector<int32_t>& cycle, std::vector<int32_t>& ans) {
  int32_t last = 0;
  for (size_t i = 0; i < cycle.size(); ++i) {
    last = cycle[last];
  }
  int32_t copy_last = last;
  ans.emplace_back(last);
  last = cycle[last];
  while (last != copy_last) {
    ans.emplace_back(last);
    last = cycle[last];
  }
  ans.emplace_back(copy_last);
}

bool HasNegativeCycle(const Graph& graph, std::vector<int32_t>& ans) {
  std::vector<int64_t> dist(graph.n + 1, kMax);
  std::vector<int32_t> cycle(graph.n + 1);
  for (int32_t j = 0; j < graph.n; ++j) {
    for (const auto& edge : graph.edges) {
      Relax(edge, dist, cycle);
    }
  }
  for (const auto& edge : graph.edges) {
    if (Relax(edge, dist, cycle)) {
      FormReversedCorrectCycle(cycle, ans);
      return true;
    }
  }
  return false;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 1; i < graph.n + 1; ++i) {
    graph.edges.emplace_back(i, 0, 0);
    for (int32_t j = 1; j < graph.n + 1; ++j) {
      int32_t weight = 0;
      io >> weight;
      if (weight != kConst) {
        graph.edges.emplace_back(i, j, weight);
      }
    }
  }
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  std::cin >> n;
  Graph graph(n);
  std::cin >> graph;
  std::vector<int32_t> cycle(n + 1);
  std::vector<int32_t> ans;
  if (HasNegativeCycle(graph, ans)) {
    std::cout << "YES\n";
    std::cout << ans.size() << '\n';
    for (auto i = static_cast<int32_t>(ans.size() - 1); i >= 0; --i) {
      std::cout << ans[i] << ' ';
    }
  } else {
    std::cout << "NO";
  }
  return 0;
}
