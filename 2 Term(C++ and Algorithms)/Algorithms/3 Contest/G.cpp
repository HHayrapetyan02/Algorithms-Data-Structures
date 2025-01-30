#include <iostream>
#include <vector>
#include <limits>

const auto kInf = std::numeric_limits<int32_t>::max();
const auto kDist = 30000;

struct Edge {
  int32_t begin = 0;
  int32_t end = 0;
  int32_t weight = 0;
  Edge() = default;
  Edge(const int32_t& begin, const int32_t& end, const int32_t& weight) : begin(begin), end(end), weight(weight) {
  }
};

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<Edge> edges_;

 public:
  Graph() = default;
  explicit Graph(int32_t, int32_t);
  void Relax(const Edge&, std::vector<int32_t>&);
  void BellmanFord(std::vector<int32_t>&);
  friend std::istream& operator>>(std::istream&, Graph&);
  friend std::ostream& operator<<(std::ostream&, std::vector<int32_t>&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), edges_(m + 1) {
}

void Graph::Relax(const Edge& edge, std::vector<int32_t>& dist) {
  if (dist[edge.end] > dist[edge.begin] + edge.weight && dist[edge.begin] != kInf) {
    dist[edge.end] = dist[edge.begin] + edge.weight;
  }
}

void Graph::BellmanFord(std::vector<int32_t>& dist) {
  dist[1] = 0;
  for (int32_t i = 0; i < n_ - 1; ++i) {
    for (const auto& edge : edges_) {
      Relax(edge, dist);
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 0; i < graph.m_; ++i) {
    int32_t begin = 0;
    int32_t end = 0;
    int32_t weight = 0;
    io >> begin >> end >> weight;
    graph.edges_.emplace_back(begin, end, weight);
  }
  return io;
}

std::ostream& operator<<(std::ostream& os, std::vector<int32_t>& dist) {
  for (size_t i = 1; i < dist.size(); ++i) {
    if (dist[i] == kInf) {
      os << kDist << " ";
    } else {
      os << dist[i] << " ";
    }
  }
  return os;
}

int main() {
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  std::vector<int32_t> dist(n + 1, kInf);
  graph.BellmanFord(dist);
  std::cout << dist << "\n";
  return 0;
}
