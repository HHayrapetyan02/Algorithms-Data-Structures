#include <iostream>
#include <vector>
#include <deque>
#include <limits>

using Vertex = int32_t;
using Weight = int32_t;
const auto kInf = std::numeric_limits<int32_t>::max();

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<std::vector<std::pair<Vertex, Weight>>> adj_;

 public:
  Graph() = default;
  Graph(const int32_t&, const int32_t&);
  int32_t BFS01(Vertex, Vertex);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(const int32_t& n, const int32_t& m) : n_(n), m_(m), adj_(n + 1) {
}

int32_t Graph::BFS01(Vertex begin, Vertex end) {
  std::vector<int32_t> dist(n_ + 1, kInf);
  dist[begin] = 0;

  std::deque<Vertex> queue{begin};
  while (!queue.empty()) {
    auto curr = queue.front();
    queue.pop_front();
    for (const auto& edge : adj_[curr]) {
      Vertex vertex = edge.first;
      Weight weight = edge.second;
      if (weight == 1) {
        if (dist[curr] + weight < dist[vertex]) {
          queue.emplace_back(vertex);
          dist[vertex] = dist[curr] + weight;
        }
      } else if (weight == 0) {
        if (dist[curr] < dist[vertex]) {
          queue.emplace_front(vertex);
          dist[vertex] = dist[curr];
        }
      }
    }
  }
  if (dist[end] == kInf) {
    return -1;
  }
  return dist[end];
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.adj_.resize(graph.n_ + 1);
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj_[begin].emplace_back(std::make_pair(end, 0));
    bool flag = true;
    for (const auto& edge : graph.adj_[end]) {
      if (edge.first == begin && edge.second == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      graph.adj_[end].emplace_back(std::make_pair(begin, 1));
    }
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  int32_t k = 0;
  std::cin >> k;
  for (int32_t i = 0; i < k; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    std::cin >> begin >> end;
    std::cout << graph.BFS01(begin, end) << "\n";
  }
  return 0;
}
