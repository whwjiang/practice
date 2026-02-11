#include <bits/stdc++.h>
using namespace std;

/*
Problem Link: https://codeforces.com/problemset/problem/2185/F
Key Insight: no key insight... my intuition guided me on this one

Solution:
The structure of the problem- 2^n nodes, xor-sums, associative operations,
repeated queries- lends itself naturally to using a segment tree. In particular,
each node in the tree can be interpreted as the xor sum for that interval. The
main thing we need to keep track of is how many nodes are above the one cow that
is potion-ed for that round.

To do that, we keep track of whether the segment has the potion-ed cow, and then
add the winner's segment length to the number of cows above the loser's
potion-ed cow, or keep the number of cows above the potion-ed cows the same if
that segment won.

*/

struct Node {
  Node() : sum(0), elements(0) {}
  Node(int val) : sum(val), elements(1) {}

  int sum;
  bool has_potion{false};
  int elements;
  int above{0};
};

void combine(const Node &l, const Node &r, Node &out) {
  out.sum = l.sum ^ r.sum;
  const Node &win = (l.sum >= r.sum) ? l : r;
  const Node &lose = (l.sum >= r.sum) ? r : l;
  if (win.has_potion) {
    out.above = win.above;
  } else if (lose.has_potion) {
    out.above = lose.above + win.elements;
  }
  out.elements = l.elements + r.elements;
  out.has_potion = l.has_potion || r.has_potion;
}

class SegmentTree {
public:
  SegmentTree(const vector<int> &a) : sz((int)a.size()) {
    st.resize(4 * sz);
    init(a, 1, 0, sz - 1);
  }

  void update(int idx, int val, bool potion) {
    return update(idx, val, potion, 1, 0, sz - 1);
  }

  int query(int start, int end) { return query(start, end, 1, 0, sz - 1); }

private:
  int sz;
  vector<Node> st;
  void init(const vector<int> &a, int at, int l, int r) {
    if (l == r) {
      st[at] = Node{a[l]};
      return;
    }
    int m = (l + r) / 2;
    init(a, at << 1, l, m);
    init(a, at << 1 | 1, m + 1, r);
    combine(st[at << 1], st[at << 1 | 1], st[at]);
  }

  void update(int idx, int val, bool potion, int at, int l, int r) {
    if (l == r) {
      Node temp(val);
      temp.has_potion = potion;
      st[at] = temp;
      return;
    }
    int m = (l + r) / 2;
    if (idx <= m) {
      update(idx, val, potion, at << 1, l, m);
    } else {
      update(idx, val, potion, at << 1 | 1, m + 1, r);
    }
    combine(st[at << 1], st[at << 1 | 1], st[at]);
  }

  int query(int start, int end, int at, int l, int r) {
    if (start > r || end < l) {
      return 0;
    }
    if (start <= l && r <= end) {
      return st[at].has_potion ? st[at].above : 0;
    }
    int m = (l + r) / 2;
    return max(query(start, end, at << 1, l, m),
               query(start, end, at << 1 | 1, m + 1, r));
  }
};

void solve() {
  int n, Q;
  cin >> n >> Q;
  int sz = 1 << n;
  vector<int> cows(sz);
  for (int i = 0; i < sz; ++i) {
    cin >> cows[i];
  }

  SegmentTree tree(cows);
  for (int q = 0; q < Q; ++q) {
    int i, power;
    cin >> i >> power;
    --i;
    int old = cows[i];
    tree.update(i, power, true);
    cout << tree.query(0, sz - 1) << endl;
    tree.update(i, old, false);
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
