#include <iostream>
#include <vector>
#include <deque>
#include <limits>

const auto kInf = std::numeric_limits<int>::max();
using Vertex = int;
using Edge = std::pair<Vertex, Vertex>;

class Graph {
 public:
  int n = 0;
  int m = 0;
  std::vector<std::vector<Vertex>> edges;

  Graph();
  explicit Graph(const int&, const int&);
  friend std::istream& operator>>(std::istream&, const Graph&);
};

Graph::Graph() : n(0), m(0), edges(0) {
}

Graph::Graph(const int& n, const int& m) : n(n), m(m) {
  edges.resize(n + 1);
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  graph.edges.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    Vertex begin = 0;
    Vertex finish = 0;
    io >> begin >> finish;
    graph.edges[begin].push_back(finish);
    graph.edges[finish].push_back(begin);
  }
  return io;
}

int64_t Distance(Graph& graph, const Vertex& begin, const Vertex& end, std::vector<Vertex>& parent) {
  std::vector<int> dist(graph.n + 1, kInf);
  dist[begin] = 0;
  std::deque<Vertex> queue{begin};
  while (!queue.empty()) {
    auto curr = queue.front();
    queue.pop_front();
    for (auto& neigh : graph.edges[curr]) {
      if (dist[neigh] == kInf) {
        dist[neigh] = dist[curr] + 1;
        parent[neigh] = curr;
        queue.emplace_back(neigh);
      }
    }
  }
  if (dist[end] == kInf) {
    return -1;
  }
  return dist[end];
}

void PrintPath(Graph& graph, const Vertex& begin, const Vertex& end, std::vector<Vertex>& parent) {
  int64_t dist = Distance(graph, begin, end, parent);
  if (dist != -1) {
    std::cout << dist << "\n";
    Vertex tmp = end;
    std::vector<Vertex> path;
    while (tmp != begin) {
      path.push_back(tmp);
      tmp = parent[tmp];
    }
    path.push_back(tmp);
    for (int i = static_cast<int>(path.size() - 1); i >= 0; --i) {
      std::cout << path[i] << " ";
    }
  } else {
    std::cout << -1 << "\n";
  }
}

int main() {
  Graph graph;
  Vertex begin = 0;
  Vertex end = 0;
  std::cin >> graph.n >> graph.m >> begin >> end >> graph;
  std::vector<Vertex> parent(graph.n + 1);
  PrintPath(graph, begin, end, parent);
  return 0;
}
