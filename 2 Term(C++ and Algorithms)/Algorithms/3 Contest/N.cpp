#include <iostream>
#include <vector>
#include <limits>

using Vertex = int32_t;
using Volume = int32_t;
const auto kInf = std::numeric_limits<int32_t>::max();

struct Edge {
  Vertex begin = 0;
  Vertex end = 0;
  Volume volume = 0;
  Volume flow = 0;
  Edge() = default;
  Edge(const Vertex& begin, const Vertex& end, const Volume& volume) : begin(begin), end(end), volume(volume) {
  }
};

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<Edge> edges_;
  std::vector<std::vector<int32_t>> values_;

 public:
  Graph() = default;
  Graph(int32_t&, int32_t&);
  int32_t Reverse(const Vertex&, const Vertex&);
  int32_t DFS(std::vector<bool>&, Vertex, Vertex, int32_t);
  int32_t MaxFlow(const Vertex&, const Vertex&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t& n, int32_t& m) : n_(n), m_(m), values_(n + 1) {
}

int32_t Graph::Reverse(const Vertex& start, const Vertex& finish) {
  for (auto& reverse : values_[finish]) {
    if (edges_[reverse].end == start && edges_[reverse].begin == finish) {
      return reverse;
    }
  }
  return -1;
}

int32_t Graph::DFS(std::vector<bool>& visited, Vertex start, Vertex finish, int32_t tmp) {
  if (start != finish) {
    visited[start] = true;
    for (size_t i = 0; i < values_[start].size(); ++i) {
      Edge& edge = edges_[values_[start][i]];
      if (!visited[edge.end] && edge.flow < edge.volume) {
        int32_t flow = DFS(visited, edge.end, finish, std::min(tmp, edge.volume - edge.flow));
        if (flow <= 0) {
          continue;
        }
        edge.flow += flow;
        int32_t reverse = Reverse(start, edge.end);
        if (reverse != -1) {
          edges_[reverse].flow -= flow;
        }
        return flow;
      }
    }
    return 0;
  }
  return tmp;
}

int32_t Graph::MaxFlow(const Vertex& start, const Vertex& finish) {
  int32_t res = 0;
  int32_t tmp = -1;
  while (tmp != 0) {
    std::vector<bool> visited(n_ + 1, false);
    tmp = DFS(visited, start, finish, kInf);
    res += tmp;
  }
  return res;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    Volume volume = 0;
    io >> begin >> end >> volume;
    graph.edges_.emplace_back(begin, end, volume);
    graph.edges_.emplace_back(end, begin, 0);
    graph.values_[begin].emplace_back(graph.edges_.size() - 2);
    graph.values_[end].emplace_back(graph.edges_.size() - 1);
  }
  return io;
}

int main() {
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  Vertex start = 1;
  Vertex finish = n;
  std::cout << graph.MaxFlow(start, finish) << "\n";
  return 0;
}
