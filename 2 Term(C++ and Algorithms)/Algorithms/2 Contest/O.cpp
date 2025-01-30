#include <iostream>
#include <vector>
#include <algorithm>

using Vertex = int32_t;
using AdjList = std::vector<std::vector<Vertex>>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  AdjList adj_;

 public:
  Graph() = default;
  Graph(int32_t, int32_t);
  void DFS(std::vector<int32_t>&);
  void RecursiveDfsVisit(Vertex, std::vector<int32_t>&, std::vector<int32_t>&, std::vector<Color>&,
                         std::vector<int32_t>&, int32_t&, bool);
  int32_t Size();
  int32_t VertexSize();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), adj_(n + m + 1) {
}

void Graph::RecursiveDfsVisit(Vertex vertex, std::vector<int32_t>& time_in, std::vector<int32_t>& time_out,
                              std::vector<Color>& color, std::vector<int32_t>& articulation, int32_t& curr_time,
                              bool flag = true) {
  color[vertex] = Color::kGray;
  time_in[vertex] = time_out[vertex] = ++curr_time;
  int32_t count_child = 0;

  for (const auto& edge : adj_[vertex]) {
    if (color[edge] == Color::kGray) {
      time_out[vertex] = std::min(time_out[vertex], time_in[edge]);
    }
    if (color[edge] == Color::kWhite) {
      ++count_child;
      RecursiveDfsVisit(edge, time_in, time_out, color, articulation, curr_time, false);
      time_out[vertex] = std::min(time_out[vertex], time_out[edge]);
      if (!flag && time_in[vertex] <= time_out[edge] && vertex > n_) {
        articulation[vertex] = 1;
      }
    }
  }
  if (flag && count_child > 1 && vertex > n_) {
    articulation[vertex] = 1;
  }
  color[vertex] = Color::kBlack;
}

void Graph::DFS(std::vector<int32_t>& articulation) {
  std::vector<Color> color(n_ + m_ + 1, Color::kWhite);
  std::vector<int32_t> time_in(n_ + m_ + 1, 0);
  std::vector<int32_t> time_out(n_ + m_ + 1, 0);
  int32_t curr_time = 0;

  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    RecursiveDfsVisit(vertex, time_in, time_out, color, articulation, curr_time);
  }
}

int32_t Graph::Size() {
  return n_ + m_ + 1;
}

int32_t Graph::VertexSize() {
  return n_;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.adj_.resize(graph.n_ + graph.m_ + 1);
  int32_t count = graph.n_ + 1;
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex first = 0;
    Vertex second = 0;
    Vertex third = 0;
    io >> first >> second >> third;
    graph.adj_[count].emplace_back(first);
    graph.adj_[count].emplace_back(second);
    graph.adj_[count].emplace_back(third);
    graph.adj_[first].emplace_back(count);
    graph.adj_[second].emplace_back(count);
    graph.adj_[third].emplace_back(count);
    ++count;
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  int32_t size = graph.Size();
  std::vector<int32_t> ans;
  std::vector<int32_t> articulation(size);
  graph.DFS(articulation);
  for (int32_t i = 1; i < size; ++i) {
    if (articulation[i] != 0) {
      ans.emplace_back(i);
    }
  }
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << "\n";
  for (const auto& elem : ans) {
    std::cout << elem - graph.VertexSize() << "\n";
  }
  return 0;
}
