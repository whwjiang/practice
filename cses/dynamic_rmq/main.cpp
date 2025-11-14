#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

template <typename T> class SegmentTree {
public:
  SegmentTree(const vector<T> &vals) : n(vals.size()) {
    tree.resize(4 * n);
    build(1, 0, n - 1, vals);
  }
  void update(size_t index, T val) { update(index, val, 1, 0, n - 1); }
  T query(size_t start, size_t end) { return query(start, end, 1, 0, n - 1); }

private:
  vector<T> tree;
  size_t n;
  void build(size_t at, size_t l, size_t r, const vector<T> &vals) {
    if (l == r) {
      tree[at] = vals[l];
      return;
    }
    size_t mid = (l + r) / 2;
    build(at << 1, l, mid, vals);
    build(at << 1 | 1, mid + 1, r, vals);
    tree[at] = min(tree[at << 1], tree[at << 1 | 1]);
  }
  void update(size_t index, T val, size_t at, size_t l, size_t r) {
    if (l == r) {
      tree[at] = val;
      return;
    }
    size_t mid = (l + r) / 2;
    if (index <= mid) {
      update(index, val, at << 1, l, mid);
    } else {
      update(index, val, at << 1 | 1, mid + 1, r);
    }
    tree[at] = min(tree[at << 1], tree[at << 1 | 1]);
  }
  T query(size_t start, size_t end, size_t at, size_t l, size_t r) {
    if (start > r || end < l) {
      return numeric_limits<T>::max();
    }
    if (start <= l && r <= end) {
      return tree[at];
    }
    size_t mid = (l + r) / 2;
    return min(query(start, end, at << 1, l, mid),
               query(start, end, at << 1 | 1, mid + 1, r));
  }
};

void solve() {
  ui n, q;
  cin >> n >> q;
  vector<ui> vals(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> vals[i];
  }
  ui type, a, b;
  SegmentTree<ui> st(vals);
  for (size_t i = 0; i < q; ++i) {
    cin >> type >> a >> b;
    if (type == 1) {
      st.update(a - 1, b);
    } else {
      cout << st.query(a - 1, b - 1) << endl;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
