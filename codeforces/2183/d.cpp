#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

// #define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2183/D1
Key Insight: A greedy approach usually works...

Solution:
Two key observations:
1. Because nodes at the same depth cannot be colored the same color, the lower
bound on the number of operations is the maximum number of nodes in a single
level

2. In the case that all of the nodes in a level belong to the same parent, we
have to add 1 to the answer

*/

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n + 1);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int> depth(n + 1);
  vector<int> parent(n + 1);
  vector<vector<int>> depthCount(n + 2);
  function<void(int, int)> dfs = [&](int cur, int d) {
    depth[cur] = d;
    depthCount[d].push_back(cur);
    // cout << cur << ": " << d << ", " << parent[cur] << endl;
    for (const auto &next : adj[cur]) {
      if (depth[next] == 0) {
        parent[next] = cur;
        dfs(next, d + 1);
      }
    }
  };
  dfs(1, 1);
  size_t ans = 1;
  for (int i = 2; i <= n + 1; ++i) {
    if (depthCount[i].empty()) {
      break;
    }
    ans = max(ans, depthCount[i].size());
    int p = parent[depthCount[i][0]];
    bool flag = false;
    for (auto cur : depthCount[i]) {
      if (p != parent[cur]) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      ans = max(ans, depthCount[i].size() + 1);
    }
  }
  cout << ans << endl;
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
