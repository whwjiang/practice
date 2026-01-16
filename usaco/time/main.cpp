#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

int MAX_DAYS = 1000;

void solve() {
  ifstream read("time.in");
  int n, m, c;
  read >> n >> m >> c;
  vector<int> money(n, 0);
  for (int i = 0; i < n; ++i) {
    read >> money[i];
  }
  vector<vector<int>> adjList(n);
  for (int i = 0; i < m; ++i) {
    int a, b;
    read >> a >> b;
    a--;
    b--;
    adjList[a].push_back(b);
  }
  vector<vector<int>> dp(MAX_DAYS + 1, vector<int>(n, -1));
  dp[0][0] = 0;
  int ans = 0;
  for (auto next : adjList[0]) {
    dp[1][next] = money[next];
  }
  for (int t = 1; t <= MAX_DAYS; ++t) {
    for (int i = 0; i < n; ++i) {
      if (dp[t - 1][i] == -1) {
        continue;
      }
      for (auto j : adjList[i]) {
        dp[t][j] = max(dp[t][j], dp[t - 1][i] + money[j]);
      }
    }
    ans = max(ans, dp[t][0] - c * t * t);
  }
  ofstream("time.out") << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
