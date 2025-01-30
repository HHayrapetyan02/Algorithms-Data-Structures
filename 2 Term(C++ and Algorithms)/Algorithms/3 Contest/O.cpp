#include <iostream>
#include <vector>
#include <limits>
#include <queue>

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
  bool BFS(std::vector<Vertex>&, Vertex, Vertex);
  int32_t MaxFlow(const Vertex&, const Vertex&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t& n, int32_t& m) : n_(n), m_(m) {
  values_.resize(n + 1);
  edges_.resize(1);
}

bool Graph::BFS(std::vector<Vertex>& parent, Vertex start, Vertex finish) {
  std::queue<int32_t> queue;
  queue.emplace(start);
  while (!queue.empty()) {
    Vertex curr = queue.front();
    queue.pop();
    for (const auto& neigh : values_[curr]) {
      Edge edge = edges_[neigh];
      if (parent[edge.end] == 0 && edge.end != start && edge.volume > edge.flow) {
        parent[edge.end] = neigh;
        queue.emplace(edge.end);
        if (edge.end != finish) {
          continue;
        }
        return true;
      }
    }
  }
  return false;
}

int32_t Graph::MaxFlow(const Vertex& start, const Vertex& finish) {
  int32_t res = 0;
  std::vector<int32_t> parent(n_ + 1, 0);
  while (BFS(parent, start, finish)) {
    auto tmp = kInf;
    Vertex tmp_vert = finish;
    while (tmp_vert != start) {
      Edge edge = edges_[parent[tmp_vert]];
      tmp = std::min(tmp, edge.volume - edge.flow);
      tmp_vert = edge.begin;
    }
    tmp_vert = finish;
    while (tmp_vert != start) {
      edges_[parent[tmp_vert]].flow += tmp;
      edges_[parent[tmp_vert] + 1].flow -= tmp;
      tmp_vert = edges_[parent[tmp_vert]].begin;
    }
    res += tmp;
    std::fill(parent.begin(), parent.end(), 0);
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
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
