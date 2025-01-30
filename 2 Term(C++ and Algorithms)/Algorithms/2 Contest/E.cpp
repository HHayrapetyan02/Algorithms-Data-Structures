#include <iostream>
#include <vector>
#include <deque>
#include <limits>

using Vertex = int;
const auto kInf = std::numeric_limits<int>::max();
const int kMax = 100000;

class Graph {
 public:
  int n = 0;
  int m = 0;
  std::vector<std::vector<Vertex>> adj;

  Graph();
  explicit Graph(const int&, const int&);
  friend std::istream& operator>>(std::istream&, const Graph&);
};

Graph::Graph() : n(0), m(0), adj(0) {
}

Graph::Graph(const int& n, const int& m) : n(n), m(m) {
  adj.resize(n + 1);
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  graph.adj.resize(graph.n + kMax);
  for (int i = 0; i < graph.m; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    int value = 0;
    io >> begin >> end >> value;
    int count = graph.n + 1;
    while (value > 1) {
      ++graph.n;
      graph.adj[begin].emplace_back(count);
      begin = count;
      ++count;
      --value;
    }
    graph.adj[begin].emplace_back(end);
  }
  return io;
}

int64_t BFS(Graph& graph, const Vertex& start, const Vertex& end) {
  std::vector<int> dist(graph.n + 1, kInf);
  dist[start] = 0;
  std::deque<Vertex> queue{start};
  while (!queue.empty()) {
    auto curr = queue.front();
    queue.pop_front();
    for (auto neigh : graph.adj[curr]) {
      if (dist[neigh] == kInf) {
        dist[neigh] = dist[curr] + 1;
        queue.emplace_back(neigh);
      }
    }
  }
  if (dist[end] == kInf) {
    return -1;
  }
  return dist[end];
}

void Print(Graph& graph, const Vertex& begin, const Vertex& end) {
  int64_t dist = BFS(graph, begin, end);
  if (dist != -1) {
    std::cout << dist << "\n";
  } else {
    std::cout << -1 << "\n";
  }
}

int main() {
  Graph graph;
  Vertex begin = 0;
  Vertex end = 0;
  std::cin >> graph.n >> graph.m >> begin >> end >> graph;
  Print(graph, begin, end);
  return 0;
}
