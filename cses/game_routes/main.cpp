#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

int MOD = 1e9 + 7;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adjList(n);
  vector<vector<int>> backEdges(n);
  vector<int> indeg(n, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adjList[--a].push_back(--b);
    backEdges[b].push_back(a);
    indeg[b]++;
  }
  deque<int> q;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      q.push_back(i);
    }
  }
  vector<int> topoOrder;
  topoOrder.reserve(n);
  while (!q.empty()) {
    int cur = q.back();
    q.pop_back();
    topoOrder.push_back(cur);
    for (const auto &next : adjList[cur]) {
      indeg[next]--;
      if (indeg[next] == 0) {
        q.push_back(next);
      }
    } 
  }
  vector<int> dp(n, 0);
  dp[0] = 1;
  for (const auto &cur : topoOrder) {
    for (const auto &prev : backEdges[cur]) {
      dp[cur] += dp[prev];
      dp[cur] %= MOD;
    }
  }
  cout << dp[n - 1] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
