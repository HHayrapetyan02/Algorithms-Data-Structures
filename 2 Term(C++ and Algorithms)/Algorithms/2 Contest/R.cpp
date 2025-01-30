#include <iostream>
#include <vector>
#include <deque>
#include <limits>

using Vertex = int64_t;
using Weight = int64_t;
const auto kInf = std::numeric_limits<int64_t>::max();
const auto kWeight = 30;

class Graph {
  int64_t n_ = 0;
  int64_t m_ = 0;
  std::vector<std::vector<std::pair<Vertex, Weight>>> adj_;

 public:
  Graph() = default;
  Graph(int64_t, int64_t);
  int64_t BFS0k(Vertex, Vertex, int);
  friend std::istream& operator>>(std::istream&, Graph&);
  void PrintVertex();
};

Graph::Graph(int64_t n, int64_t m) : n_(n), m_(m), adj_(n + 1) {
}

int64_t Graph::BFS0k(Vertex start, Vertex end, int k) {
  std::vector<int64_t> dist(n_ + 1, kInf);
  dist[start] = 0;
  int count = 1;

  std::vector<std::deque<int64_t>> queue(k);
  queue[0].emplace_front(start);
  while (count) {
    int64_t tmp = 0;
    while (queue[tmp].empty()) {
      ++tmp;
    }
    tmp %= k;
    auto curr = queue[tmp].front();
    queue[tmp].pop_front();
    --count;
    for (auto edge : adj_[curr]) {
      Vertex vertex = edge.first;
      Weight weight = edge.second;
      if (dist[curr] == kInf || dist[vertex] > dist[curr] + weight) {
        dist[vertex] = dist[curr] + weight;
        queue[dist[vertex] % k].emplace_back(vertex);
        ++count;
      }
    }
  }
  if (dist[end] == kInf) {
    return -1;
  }
  return dist[end];
}

void Graph::PrintVertex() {
  std::cin >> n_ >> m_;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  graph.adj_.resize(graph.n_ + 1);
  for (int64_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    Weight weight = 0;
    io >> begin >> end >> weight;
    graph.adj_[begin].emplace_back(std::make_pair(end, weight));
  }
  return io;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  Vertex begin = 0;
  Vertex end = 0;
  graph.PrintVertex();
  std::cin >> begin >> end >> graph;
  int64_t dist = graph.BFS0k(begin, end, kWeight);
  if (dist != -1) {
    std::cout << dist << "\n";
  } else {
    std::cout << -1 << "\n";
  }
  return 0;
}
