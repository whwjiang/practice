#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/blog/entry/151174
Key Insight: realizing that this was DP, again...

Solution:
We want to frame the IFS recursively: how can we count the number of steps in
terms of some node and its subtree? We need to make two key observations:

1. Going from a subtree to its parent, the subtree will be unmarked
2. All vertices are blank when they first start

We can define a subproblem dp[i] = the time it takes to travel from i to its
parent. In particular, dp[i] = 1 if i is a leaf, and dp[i] = dp[l] + dp[r] + 3
otherwise: the time taken for the two subtrees l and r, plus the walk that he
does to mark i as a part of IFS

From there, to get the full time taken to get to node 0 from each node, we
simply go down the tree and add each node's dp[i] to its children.
*/

constexpr int MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1);
  for (int i = 1; i <= n; ++i) {
    int l, r;
    cin >> l >> r;
    if (l != 0 && r != 0) {
      adj[i].push_back(l);
      adj[i].push_back(r);
    }
  }
  vector<int> dp(n + 1);
  function<int(int)> dp1 = [&](int cur) -> int {
    if (adj[cur].empty()) {
      return dp[cur] = 1;
    }
    return dp[cur] = (dp1(adj[cur][0]) + dp1(adj[cur][1]) + 3) % MOD;
  };
  dp1(1);

  function<void(int)> dp2 = [&](int cur) {
    if (adj[cur].empty()) {
      return;
    }
    dp[adj[cur][0]] += dp[cur];
    dp[adj[cur][0]] %= MOD;
    dp[adj[cur][1]] += dp[cur];
    dp[adj[cur][1]] %= MOD;
    dp2(adj[cur][0]);
    dp2(adj[cur][1]);
  };
  dp2(1);

  for (int i = 1; i <= n; ++i) {
    cout << dp[i] << ' ';
  }
  cout << endl;
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
