#include <bits/stdc++.h>
using namespace std;

// #define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2184/F
Key Insight: realizing that the subproblems are identical, so we can use DP

Solution:
I think realizing that the solution is DP and framing the subproblems is quite
challenging, but the implementation is pretty straightforward. Observations:

1. The number of times you shake vertices of the tree are all congruent mod 3 -
we only care about if it is divisible by 3, not the actual number
2. Collecting all the cherries is a recursive problem that can be built up
depending on a node and its children

This leads to the subproblem dp[i][j]: whether the subtree rooted at i can have
its cherries successfully collected in a number of shaken vertices congruent to
j mod 3.

Base case: for any leaf i, dp[i][1] = 1
Transition: at any vertex i, there are two choices:
1. If we decide not to shake the vertex i, then we set dp[i][0] to true and we
need to collect on i's children. Note dp[i][0] = true because before we process
any children, the children nodes are the empty set. We then accumulate on the
children's dp (look at merge code)

2. If we do shake the vertex i, then dp[i][1] = true (note that this combines
with the base case)
Answer: dp[1][0]
*/

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1);
  vector<int> indeg(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<vector<bool>> dp(n + 1, vector<bool>(3, false));

  auto merge = [&](const vector<bool> &r, const vector<bool> &l,
                   vector<bool> &out) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (r[i] && l[j])
          out[(i + j) % 3] = true;
      }
    }
  };
  function<void(int, int)> dfs = [&](int cur, int p) {
    vector<int> children;
    for (const auto &next : adj[cur]) {
      if (next != p) {
        dfs(next, cur);
        children.push_back(next);
      }
    }
    if (!children.empty()) {
      dp[cur][0] = true;
      for (const auto &next : children) {
        vector<bool> result(3, false);
        merge(dp[cur], dp[next], result);
        dp[cur] = std::move(result);
      }
    }
    dp[cur][1] = true;
  };
  dfs(1, -1);
  cout << (dp[1][0] == true ? "YES" : "NO") << endl;
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
