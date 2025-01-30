#include <iostream>
#include <vector>
#include <algorithm>

using Vertex = int32_t;
using AdjList = std::vector<std::vector<Vertex>>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
 public:
  int32_t n = 0;
  int32_t m = 0;
  AdjList adj;

  Graph() = default;
  Graph(const int32_t&, const int32_t&);
  void DFS(std::vector<int32_t>&);
  void RecursiveDfsVisit(Vertex, std::vector<int32_t>&, std::vector<int32_t>&, std::vector<Color>&,
                         std::vector<int32_t>&, int32_t&, bool);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(const int32_t& n, const int32_t& m) : n(n), m(m), adj(n + 1) {
}

void Graph::RecursiveDfsVisit(Vertex vertex, std::vector<int32_t>& time_in, std::vector<int32_t>& time_out,
                              std::vector<Color>& color, std::vector<int32_t>& articulation, int32_t& curr_time,
                              bool flag = true) {
  color[vertex] = Color::kGray;
  time_in[vertex] = time_out[vertex] = ++curr_time;
  int32_t count_child = 0;

  for (auto edge : adj[vertex]) {
    if (color[edge] == Color::kGray) {
      time_out[vertex] = std::min(time_out[vertex], time_in[edge]);
    }
    if (color[edge] == Color::kWhite) {
      ++count_child;
      RecursiveDfsVisit(edge, time_in, time_out, color, articulation, curr_time, false);
      time_out[vertex] = std::min(time_out[edge], time_out[vertex]);
      if (!flag && time_in[vertex] <= time_out[edge]) {
        articulation[vertex] = 1;
      }
    }
  }
  if (flag && count_child > 1) {
    articulation[vertex] = 1;
  }
  color[vertex] = Color::kBlack;
}

void Graph::DFS(std::vector<int32_t>& articulation) {
  std::vector<Color> color(n + 1, Color::kWhite);
  std::vector<int32_t> time_in(n + 1, 0);
  std::vector<int32_t> time_out(n + 1, 0);
  int32_t curr_time = 0;

  for (Vertex vertex = 1; vertex < n + 1; ++vertex) {
    RecursiveDfsVisit(vertex, time_in, time_out, color, articulation, curr_time);
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n >> graph.m;
  graph.adj.resize(graph.n + 1);
  for (int32_t i = 0; i < graph.m; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj[begin].emplace_back(end);
    graph.adj[end].emplace_back(begin);
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<Vertex> articulation(graph.n + 1);
  std::vector<int32_t> ans;
  graph.DFS(articulation);
  for (Vertex vertex = 1; vertex < graph.n + 1; ++vertex) {
    if (articulation[vertex] != 0) {
      ans.emplace_back(vertex);
    }
  }
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << "\n";
  for (const auto& elem : ans) {
    std::cout << elem << "\n";
  }
  return 0;
}
