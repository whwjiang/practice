#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

template <typename T> class SegmentTree {
public:
  SegmentTree(const vector<T> &vals) : n(vals.size()) {
    tree.resize(4 * n);
    build(vals, 1, 0, n - 1);
  }
  SegmentTree(size_t n_vals) : n(n_vals) { tree = vector<T>(4 * n, DEFAULT); }
  void update(size_t index, T val) { return update(index, val, 1, 0, n - 1); }
  T query(size_t start, size_t end) { return query(start, end, 1, 0, n - 1); }

private:
  T DEFAULT = T();
  vector<T> tree;
  size_t n;
  T combine(const T &a, const T &b) { return max(a, b); }
  void build(const vector<T> &vals, size_t at, size_t l, size_t r) {
    if (l == r) {
      tree[at] = vals[l];
      return;
    }
    size_t mid = (l + r) / 2;
    build(vals, at << 1, l, mid);
    build(vals, at << 1 | 1, mid + 1, r);
    tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
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
    tree[at] = combine(tree[at << 1], tree[at << 1 | 1]);
  }
  T query(size_t start, size_t end, size_t at, size_t l, size_t r) {
    if (start > r || end < l) {
      return DEFAULT;
    }
    if (start <= l && r <= end) {
      return tree[at];
    }
    size_t mid = (l + r) / 2;
    return combine(query(start, end, at << 1, l, mid),
                   query(start, end, at << 1 | 1, mid + 1, r));
  }
};

void solve() {
  // dp[i]: longest sequence starting at i
  // dp[i] = max over mountains within bounds k dp[k] + 1
  // base case: lowest mountains have dp[k] = 1
  // process mountains of the same height at the same time, in increasing
  // order.
  size_t n;
  cin >> n;
  vector<int> h(n);
  vector<pair<int, size_t>> index;
  index.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> h[i];
    index.push_back({h[i], i});
  }
  sort(index.begin(), index.end());

  deque<int> s;
  vector<int> pgi(n, -1);
  vector<int> ngi(n, (int)n);

  for (int i = 0; i < (int)n; ++i) {
    while (!s.empty() && h[s.back()] < h[i]) {
      ngi[s.back()] = i;
      s.pop_back();
    }
    s.push_back(i);
  }
  s.clear();
  for (int i = (int)n - 1; i >= 0; --i) {
    while (!s.empty() && h[s.back()] < h[i]) {
      pgi[s.back()] = i;
      s.pop_back();
    }
    s.push_back(i);
  }
  SegmentTree<int> st(n);
  size_t j = 0;
  vector<int> dp(n, 0);
  for (size_t i = 0; i < n;) {
    while (index[i].first == index[j].first) {
      ++j;
    }
    for (size_t k = i; k < j; ++k) {
      size_t idx = index[k].second;
      int left = pgi[idx];
      int right = ngi[idx];
      dp[idx] = 1 + st.query(left + 1, right - 1);
    }
    for (size_t k = i; k < j; ++k) {
      size_t idx = index[k].second;
      st.update(idx, dp[idx]);
    }
    i = j;
  }
  int ans = 0;
  for (size_t i = 0; i < n; ++i) {
    ans = max(ans, dp[i]);
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
