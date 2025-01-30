#include <iostream>
#include <vector>
#include <queue>

using Vertex = int32_t;
using Weight = int32_t;
using Edge = std::pair<Weight, Vertex>;
using Edges = std::vector<std::vector<std::pair<Vertex, Weight>>>;
const auto kDist = 2009000999;

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  Edges edges_;

 public:
  Graph() = default;
  explicit Graph(int32_t, int32_t);
  int32_t Size();
  void Dijkstra(Vertex&, std::vector<int32_t>&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m) {
  edges_.resize(n);
}

int32_t Graph::Size() {
  return n_;
}

void Graph::Dijkstra(Vertex& vertex, std::vector<int32_t>& dist) {
  dist[vertex] = 0;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
  queue.emplace(0, vertex);

  while (!queue.empty()) {
    Vertex vertex = queue.top().second;
    Weight weight = queue.top().first;
    queue.pop();

    if (weight <= dist[vertex]) {
      for (const auto& neigh : edges_[vertex]) {
        if (dist[neigh.first] > dist[vertex] + neigh.second) {
          dist[neigh.first] = dist[vertex] + neigh.second;
          queue.emplace(dist[neigh.first], neigh.first);
        }
      }
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    Weight weight = 0;
    io >> begin >> end >> weight;
    graph.edges_[begin].emplace_back(std::make_pair(end, weight));
    graph.edges_[end].emplace_back(std::make_pair(begin, weight));
  }
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int32_t n = 0;
    int32_t m = 0;
    std::cin >> n >> m;
    Graph graph(n, m);
    std::cin >> graph;
    Vertex vertex = 0;
    std::cin >> vertex;
    std::vector<int32_t> dist(graph.Size(), kDist);
    graph.Dijkstra(vertex, dist);
    for (const auto& distance : dist) {
      std::cout << (distance == kDist ? kDist : distance) << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
