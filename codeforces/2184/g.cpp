#include <bits/stdc++.h>
using namespace std;

// #define int long long
/*
Problem Link:
Key Insight:

Solution:

*/

class SegmentTree {
public:
  SegmentTree(const vector<int> &vals) : n(vals.size()) {
    tree.resize(4 * n);
    build(vals, 1, 0, n - 1);
  }

  void update(int val, int idx) {
    return update(val, idx, 1, 0, n - 1);
  }

  int query(int start, int end) {
    return query(start, end, 1, 0, n - 1);
  }

private:
  vector<int> tree;
  int n;

  void build(const vector<int> &vals, int at, int l, int r) {
    if (l == r) {
      tree[at] = vals[l];
      return;
    }
    int mid = (l + r) / 2;
    build(vals, at << 1, l, mid);
    build(vals, at << 1 | 1, mid + 1, r);
    tree[at] = min(tree[at << 1], tree[at << 1 | 1]);
  }

  void update(int val, int idx, int at, int l, int r) {
    if (l == r) {
      tree[at] = val;
      return;
    }
    int mid = (l + r) / 2;
    if (idx <= mid) {
      update(val, idx, at << 1, l, mid);
    } else {
      update(val, idx, at << 1 | 1, mid + 1, r);
    }
    tree[at] = min(tree[at << 1], tree[at << 1 | 1]);
  }

  int query(int start, int end, int at, int l, int r) {
    if (r < start || end < l) {
      return INT_MAX;
    }
    if (start <= l && r <= end) {
      return tree[at];
    }
    int mid = (l + r) / 2;
    return min(query(start, end, at << 1, l, mid),
               query(start, end, at << 1 | 1, mid + 1, r));
  }
};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> vals(n);
  for (int i = 0; i < n; ++i) {
    cin >> vals[i];
  }

  SegmentTree st(vals);
  auto nasty = [&](int start, int end) {
    int l = start, r = end;
    while (l <= r) {
      // cout << "at " << l << ' ' << r << endl;
      int mid = (l + r) / 2;
      int mn = st.query(start, mid);
      // cout << "  mn: " << mn << ", mid: " << mid << endl;
      if (mn < mid) {
        r = mid - 1;
      } else if (mn > mid) {
        l = mid + 1;
      } else {
        return true;
      }
    }
    return false;
  };

  for (int i = 0; i < n; ++i) {
    int type, a, b;
    cin >> type >> a >> b;
    if (type == 1) {
      st.update(b, --a);
    } else {
      cout << nasty(--a, --b) << endl;
    }
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
}
