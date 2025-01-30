#include <iostream>
#include <vector>
#include <algorithm>

using Vertex = int32_t;
using Edge = std::pair<Vertex, Vertex>;
using AdjList = std::vector<std::vector<Edge>>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  AdjList adj_;
  std::vector<Edge> edges_;
  std::vector<int32_t> degree_;

 public:
  Graph() = default;
  Graph(int32_t, int32_t);
  void DFS(std::vector<Vertex>&);
  void RecursiveDfsVisit(Vertex, Vertex, std::vector<Vertex>&, std::vector<int32_t>&, std::vector<int32_t>&,
                         std::vector<Color>&, int32_t&);
  int32_t Count();
  int32_t Othercount(std::vector<Vertex>&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), adj_(n + 1), edges_(m + 1), degree_(n + 1) {
}

void Graph::RecursiveDfsVisit(Vertex vertex, Vertex parent, std::vector<Vertex>& bridges, std::vector<int32_t>& time_in,
                              std::vector<int32_t>& time_out, std::vector<Color>& color, int32_t& curr_time) {
  color[vertex] = Color::kGray;
  time_in[vertex] = time_out[vertex] = ++curr_time;

  for (const auto& u : adj_[vertex]) {
    if (u.first != parent) {
      if (color[u.first] == Color::kGray) {
        time_out[vertex] = std::min(time_out[vertex], time_in[u.first]);
      }
      if (color[u.first] == Color::kWhite) {
        RecursiveDfsVisit(u.first, vertex, bridges, time_in, time_out, color, curr_time);
        time_out[vertex] = std::min(time_out[u.first], time_out[vertex]);
        if (time_in[vertex] < time_out[u.first]) {
          int32_t count = 0;
          for (const auto& k : adj_[vertex]) {
            if (k.first == u.first) {
              ++count;
            }
          }
          if (count == 1) {
            bridges.emplace_back(u.second);
          }
        }
      }
    }
  }
  color[vertex] = Color::kBlack;
}

void Graph::DFS(std::vector<Vertex>& bridges) {
  std::vector<int32_t> time_in(n_ + 1, 0);
  std::vector<int32_t> time_out(n_ + 1, 0);
  std::vector<Color> color(n_ + 1, Color::kWhite);
  int32_t curr_time = 0;
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite) {
      RecursiveDfsVisit(vertex, 0, bridges, time_in, time_out, color, curr_time);
    }
  }
}

int32_t Graph::Count() {
  int32_t count = 0;
  auto adj_size = static_cast<int32_t>(adj_.size());
  for (Vertex vertex = 1; vertex < adj_size; ++vertex) {
    if (adj_[vertex].size() <= 1) {
      auto size = static_cast<int32_t>(adj_[vertex].size());
      count += 2 - size;
    }
  }
  return count % 2 == 0 ? count / 2 : count / 2 + 1;
}

int32_t Graph::Othercount(std::vector<Vertex>& bridges) {
  int32_t count = 0;
  for (size_t i = 0; i < bridges.size(); ++i) {
    auto tmp = edges_[bridges[i] - 1];
    if (degree_[tmp.first] >= 3 && degree_[tmp.second] >= 3) {
      ++count;
    }
  }
  return count;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.adj_.resize(graph.n_ + 1);
  graph.degree_.resize(graph.n_ + 1);
  for (int32_t i = 1; i < graph.m_ + 1; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj_[begin].emplace_back(std::make_pair(end, i));
    graph.adj_[end].emplace_back(std::make_pair(begin, i));
    Edge rebro = std::make_pair(begin, end);
    graph.edges_.emplace_back(rebro);
    ++graph.degree_[begin];
    ++graph.degree_[end];
  }
  return io;
}

int32_t main() {
  Graph graph;
  std::cin >> graph;
  std::vector<Vertex> bridges;

  graph.DFS(bridges);
  int32_t count_first = graph.Count();
  int32_t count_second = graph.Othercount(bridges);
  if (count_first >= 2 && count_second >= 1) {
    std::cout << count_first << "\n";
  } else if (count_second >= 1) {
    ++count_first;
    std::cout << count_first << "\n";
  } else {
    std::cout << count_first << "\n";
  }
  return 0;
}
