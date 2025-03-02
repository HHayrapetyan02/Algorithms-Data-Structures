#include <iostream>
#include <vector>

struct Query {
  char category = ' ';
  int l = 0;
  int r = 0;
  int add = 0;
  Query() : category(' '), l(0), r(0), add(0) {
  }
  Query(char category, int l, int r, int add = 0) : category(category), l(l), r(r), add(add) {
  }
};

class SegmentTree {
  std::vector<std::pair<int, int>> segment_tree_;

 public:
  explicit SegmentTree(std::vector<int>&);
  void BuildSegTree(std::vector<int>&, int, int, int);
  void Push(int);
  int Max(int, int, int, Query&);
  void Add(int, int, int, Query&);
};

SegmentTree::SegmentTree(std::vector<int>& vec) : segment_tree_(4 * vec.size(), {0, 0}) {
}

void SegmentTree::BuildSegTree(std::vector<int>& values, int vertex, int tl, int tr) {
  if (tl == tr) {
    segment_tree_[vertex].first = values[tl];
  } else {
    int tm = (tl + tr) / 2;
    BuildSegTree(values, vertex * 2, tl, tm);
    BuildSegTree(values, vertex * 2 + 1, tm + 1, tr);
    segment_tree_[vertex].first = std::max(segment_tree_[vertex * 2].first, segment_tree_[vertex * 2 + 1].first);
  }
}

void SegmentTree::Push(int vertex) {
  segment_tree_[vertex].first += segment_tree_[vertex].second;
  segment_tree_[vertex * 2].second += segment_tree_[vertex].second;
  segment_tree_[vertex * 2 + 1].second += segment_tree_[vertex].second;
  segment_tree_[vertex].second = 0;
}

int SegmentTree::Max(int vertex, int tl, int tr, Query& query) {
  if (query.l > query.r) {
    return 0;
  }
  if (query.l == tl && query.r == tr) {
    return segment_tree_[vertex].first + segment_tree_[vertex].second;
  }
  Push(vertex);
  int tm = (tl + tr) / 2;
  Query query1('a', query.l, std::min(query.r, tm), query.add);
  Query query2('a', std::max(query.l, tm + 1), query.r, query.add);
  int left = Max(vertex * 2, tl, tm, query1);
  int right = Max(vertex * 2 + 1, tm + 1, tr, query2);
  return std::max(left, right);
}

void SegmentTree::Add(int vertex, int tl, int tr, Query& query) {
  if (query.l > query.r) {
    return;
  }
  if (query.l == tl && query.r == tr) {
    segment_tree_[vertex].second += query.add;
  } else {
    Push(vertex);
    int tm = (tl + tr) / 2;
    Query query1('a', query.l, std::min(query.r, tm), query.add);
    Query query2('a', std::max(query.l, tm + 1), query.r, query.add);
    Query query3('a', tl, tm, 0);
    Query query4('a', tm + 1, tr, 0);
    Add(vertex * 2, tl, tm, query1);
    Add(vertex * 2 + 1, tm + 1, tr, query2);
    segment_tree_[vertex].first = std::max(Max(vertex * 2, tl, tm, query3), Max(vertex * 2 + 1, tm + 1, tr, query4));
  }
}

std::istream& operator>>(std::istream& io, std::vector<int>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    io >> vector[i];
  }
  return io;
}

std::istream& operator>>(std::istream& io, Query& query) {
  io >> query.category >> query.l >> query.r;
  if (query.category == 'm') {
    return io;
  }
  io >> query.add;
  return io;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> values(n, 0);
  SegmentTree segment_tree(values);
  std::cin >> values;
  segment_tree.BuildSegTree(values, 1, 0, n - 1);
  int m = 0;
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    Query query;
    std::cin >> query;
    --query.l;
    --query.r;
    if (query.category == 'm') {
      std::cout << segment_tree.Max(1, 0, n - 1, query) << ' ';
    } else {
      segment_tree.Add(1, 0, n - 1, query);
    }
  }
  return 0;
}
