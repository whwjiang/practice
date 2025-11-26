#include <bits/stdc++.h>
// #pragma GCC optimize("O3") 
using namespace std;
 
using ll = long long;
using ui = unsigned int;
 
int MOD = 1e9 + 7;
 
void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adjList(n);
  int to, from;
  for (int i = 0; i < m; ++i) {
    cin >> to >> from;
    to--, from--;
    adjList[to].push_back(from);
  }
  int FILL = (1 << n) - 1;
  vector<vector<int>> dp(1 << n, vector<int>(n));
  dp[1][0] = 1;
  for (int i = 0; i < (1 << n); ++i) {
    if (!(i & 1)) continue;
    if (i & (1 << (n - 1)) && i != FILL) continue;
    for (int j = 0; j < n; ++j) {
      for (int next : adjList[j]) {
        if (!dp[i][j] || (i & (1 << next))) {
          continue;
        }
        dp[i | (1 << next)][next] += dp[i][j];
        dp[i | (1 << next)][next] %= MOD;
      }
    }
  }
 
  cout << dp[(1 << n) - 1][n - 1] << endl;
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}