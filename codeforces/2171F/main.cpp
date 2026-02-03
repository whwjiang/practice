#include <bits/stdc++.h>
using namespace std;

using ll = long long;
/*
Problem Link: https://codeforces.com/problemset/problem/2171/F
Key Insight: look at the structure that emerges based on maximums and minimums
in a group

Solution:
The central idea is to make notes about what happens when you split the perm (p)
into parts. What I mean is that partitioning p into parts based on the suffix
max and the prefix min gives you a lot of information about whether p can be
turned into a tree.

Example:
     4 2 6 5 1 3
pre: 4 2 2 2 1 1
suf: 6 6 6 5 3 3 -> for each index, suf_i > pre_{i - 1}. This tells us that
                    there will be path from p_i to p_{i - 1} from p_i to suf_i
                    to pre_{i - 1}

From there, we can form a partition (l, r) where r is any index where suf_i =
p_i, and l is the first index where suf_l == suf_r, connect all nodes in a
partition together, and then connect these partitions together
*/

void solve() {
  int n;
  cin >> n;
  vector<int> p(n);
  vector<int> pre(n, 1e9);
  vector<pair<int, int>> suf(n);
  for (int i = 0; i < n; ++i) {
    cin >> p[i];
  }
  pre[0] = p[0];
  suf[n - 1] = {p[n - 1], n - 1};
  for (int i = 1; i < n; ++i) {
    pre[i] = min(pre[i - 1], p[i]);
    suf[n - 1 - i] = max(suf[n - i], {p[n - 1 - i], n - i - 1});
  }
  for (int i = 0; i < n - 1; ++i) {
    if (pre[i] > suf[i + 1].first) {
      cout << "NO" << endl;
      return;
    }
  }
  cout << "YES" << endl;
  for (int l = 0; l < n;) {
    int r = suf[l].second;
    for (int i = l; i < r; ++i) {
      cout << p[i] << ' ' << p[r] << endl;
    }
    if (l > 0) {
      cout << pre[l - 1] << ' ' << p[r] << endl;
    }
    l = r + 1;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
}
