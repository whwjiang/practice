#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

struct Node {
  ui left0{0};
  ui right0{0};
  ui left1{0};
  ui right1{0};
  ui len{0};
  ui ans{0};
  Node() {}
  Node(ui val) {
    left0 = (val == 0);
    right0 = (val == 0);
    left1 = (val == 1);
    right1 = (val == 1);
    len = 1;
    ans = 1;
  }
  Node(const Node &a, const Node &b) {
    len = a.len + b.len;
    left0 = a.left0 + (a.left0 == a.len) * b.left0;
    right0 = b.right0 + (b.right0 == b.len) * a.right0;
    left1 = a.left1 + (a.left1 == a.len) * b.left1;
    right1 = b.right1 + (b.right1 == b.len) * a.right1;
    ans = max({a.ans, b.ans, a.right0 + b.left0, a.right1 + b.left1});
  }
  friend ostream &operator<<(ostream &os, const Node &n) {
    os << n.len << ", " << n.left0 << ", " << n.right0 << ", " << n.left1
       << ", " << n.right1 << ", " << n.ans;
    return os;
  }
};

class SegmentTree {
public:
  SegmentTree(const vector<int> &vals) : n(vals.size()) {
    tree.resize(4 * n);
    build(1, 0, n - 1, vals);
  }
  void update(size_t index, int val) { update(1, 0, n - 1, index, val); }
  ui query(size_t start, size_t end) { return query(start, end, 1, 0, n - 1); }

private:
  vector<Node> tree;
  size_t n;
  void build(size_t at, size_t l, size_t r, const vector<int> &vals) {
    if (l == r) {
      tree[at] = std::move(Node(vals[l]));
      return;
    }
    size_t mid = (l + r) / 2;
    build(at << 1, l, mid, vals);
    build(at << 1 | 1, mid + 1, r, vals);
    tree[at] = std::move(Node(tree[at << 1], tree[at << 1 | 1]));
  }
  void update(size_t at, size_t l, size_t r, size_t index, int val) {
    if (l == r) {
      tree[at] = std::move(Node(val));
      return;
    }
    size_t mid = (l + r) / 2;
    if (index <= mid) {
      update(at << 1, l, mid, index, val);
    } else {
      update(at << 1 | 1, mid + 1, r, index, val);
    }
    tree[at] = std::move(Node(tree[at << 1], tree[at << 1 | 1]));
  }
  ui query(size_t start, size_t end, size_t at, size_t l, size_t r) {
    if (start > r || end < l) {
      return 0;
    }
    if (start <= l && r <= end) {
      return tree[at].ans;
    }
    size_t mid = (l + r) / 2;
    return max(query(start, end, at << 1, l, mid),
               query(start, end, at << 1 | 1, mid + 1, r));
  }
};

void solve() {
  string s;
  cin >> s;
  vector<int> vals;
  for (const auto &c : s) {
    vals.push_back(c - '0');
  }
  size_t n = vals.size();
  size_t m;
  cin >> m;
  vector<size_t> queries;
  ui cur;
  for (size_t i = 0; i < m; ++i) {
    cin >> cur;
    queries.push_back(cur - 1);
  }
  SegmentTree st(vals);
  for (size_t i = 0; i < m; ++i) {
    auto q = queries[i];
    vals[q] ^= 1;
    st.update(q, vals[q]);
    cout << st.query(0, n - 1);
    cout << ' ';
  }
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
