#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const auto kInf = 1'000'000'000;
const auto kConst = -1'000'000'000;

struct Edge {
  int32_t vertex = 0;
  int32_t weight = 0;
  Edge() = default;
  Edge(const int32_t& vertex, const int32_t& weight) : vertex(vertex), weight(weight) {
  }
  bool operator<(const Edge& other) const {
    return weight < other.weight;
  }
};

struct Graph {
  int32_t n = 0;
  int32_t m = 0;
  std::vector<std::vector<Edge>> edges;
  Graph() = default;
  Graph(const int32_t& n, const int32_t& m) : n(n), m(m) {
    edges.resize(n + 1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

void FloydWarshall(Graph& graph, std::vector<int32_t>& dist) {
  dist[graph.n] = 0;
  for (int32_t i = 1; i < graph.n; ++i) {
    for (int32_t j = 0; j < graph.n + 1; ++j) {
      for (const auto& neigh : graph.edges[j]) {
        dist[neigh.vertex] = std::min(dist[neigh.vertex], dist[j] + neigh.weight);
      }
    }
  }
  for (int32_t i = 0; i < graph.n; ++i) {
    for (auto& neigh : graph.edges[i]) {
      neigh.weight += (dist[i] - dist[neigh.vertex]);
    }
  }
}

void Dijkstra(Graph& graph, const int32_t begin, const std::vector<int32_t> dist, int32_t& max) {
  std::priority_queue<Edge> queue;
  std::vector<int32_t> interval(graph.n + 1, kConst);
  std::vector<bool> visited(graph.n + 1, false);

  queue.emplace(begin, dist[begin]);
  interval[begin] = 0;
  while (!queue.empty()) {
    Edge tmp = queue.top();
    queue.pop();
    visited[tmp.vertex] = true;
    for (const auto& neigh : graph.edges[tmp.vertex]) {
      if (!visited[neigh.vertex] && interval[tmp.vertex] > neigh.weight + interval[neigh.vertex]) {
        interval[neigh.vertex] = interval[tmp.vertex] - neigh.weight;
        queue.emplace(neigh.vertex, interval[neigh.vertex]);
      }
    }
  }
  for (int32_t i = 0; i < graph.n; ++i) {
    if (interval[i] != kConst) {
      interval[i] = (dist[i] - dist[begin] - interval[i]);
      max = std::max(max, interval[i]);
    }
  }
}

int32_t Johnson(Graph& graph) {
  std::vector<int32_t> dist(graph.n + 1, kInf);
  FloydWarshall(graph, dist);
  int32_t max = 0;
  for (int32_t i = 0; i < graph.n; ++i) {
    Dijkstra(graph, i, dist, max);
  }
  return max;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  int32_t begin = 0;
  int32_t end = 0;
  int32_t weight = 0;
  for (int32_t i = 0; i < graph.n; ++i) {
    graph.edges[graph.n].emplace_back(i, 0);
  }
  for (int32_t i = 0; i < graph.m; ++i) {
    io >> begin >> end >> weight;
    graph.edges[begin].emplace_back(end, weight);
  }
  return io;
}

int32_t main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << Johnson(graph) << "\n";
  return 0;
}
