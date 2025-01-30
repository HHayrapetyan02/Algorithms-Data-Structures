#include <iostream>
#include <vector>
#include <deque>
#include <limits>

using Vertex = int;
const auto kMax = 10000;
const auto kMin = 1111;
const auto kCountnums = 6561;
const auto kInf = std::numeric_limits<int>::max();

class Graph {
 public:
  int n = 0;
  std::vector<std::vector<Vertex>> edges;

  Graph() = default;
  explicit Graph(const int&);
};

Graph::Graph(const int& count) : n(count) {
  edges.resize(kMax);
  for (int i = kMin; i < kMax; ++i) {
    if (i % 10 != 0 && (i % 100 - i % 10) != 0 && (i % 1000 - i % 100) != 0) {
      if (i / 1000 != 9) {
        edges[i].push_back(i + 1000);
      }
      if (i % 10 != 1) {
        edges[i].push_back(i - 1);
      }
      int tmp = (i % 10) * 1000 + (i / 1000) * 100 + (i % 1000 - i % 100) / 10 + (i % 100 - i % 10) / 10;
      edges[i].push_back(tmp);
      tmp = (i / 1000) + (i % 10) * 10 + (i % 100 - i % 10) * 10 + (i % 1000 - i % 100) * 10;
      edges[i].push_back(tmp);
    }
  }
}

int64_t Distance(Graph& graph, const Vertex& begin, const Vertex& end, std::vector<Vertex>& parent) {
  std::vector<int64_t> dist(kMax, kInf);
  std::vector<bool> visited(kMax, false);

  dist[begin] = 0;
  visited[begin] = true;
  std::deque<Vertex> queue{begin};
  while (!queue.empty()) {
    auto curr = queue.front();
    queue.pop_front();
    for (auto& neigh : graph.edges[curr]) {
      if (visited[neigh]) {
        continue;
      }
      visited[neigh] = true;
      parent[neigh] = curr;
      dist[neigh] = dist[curr] + 1;
      queue.emplace_back(neigh);
    }
  }
  return dist[end];
}

void PrintPath(Graph& graph, const Vertex& begin, const Vertex& end, std::vector<Vertex>& parent) {
  int64_t dist = Distance(graph, begin, end, parent);
  std::cout << dist + 1 << "\n";
  std::vector<Vertex> path;
  Vertex tmp = end;
  while (tmp != begin) {
    path.push_back(tmp);
    tmp = parent[tmp];
  }
  path.push_back(tmp);
  for (int i = static_cast<int>(path.size() - 1); i >= 0; --i) {
    std::cout << path[i] << "\n";
  }
}

int main() {
  Vertex start = 0;
  Vertex finish = 0;
  std::cin >> start >> finish;
  Graph graph(kCountnums);
  std::vector<Vertex> parent(kMax);
  PrintPath(graph, start, finish, parent);
  return 0;
}
