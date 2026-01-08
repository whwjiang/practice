#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  freopen("feast.in", "r", stdin);
  freopen("feast.out", "w", stdout);
  int t, a, b;
  cin >> t >> a >> b;
  vector<vector<char>> dp(t + 1, vector<char>(2, 0));
  dp[0][0] = 1;
  dp[0][1] = 1;
  int ans = 0;
  for (int i = 0; i <= t; ++i) {
    if (dp[i][1]) {
      if (i + a <= t) {
        dp[i + a][1] = true;
      }
      if (i + b <= t) {
        dp[i + b][1] = true;
      }
      dp[i / 2][0] = true;
      ans = max(ans, i);
    }
  }
  for (int i = 0; i <= t; ++i) {
    if (dp[i][0]) {
      if (i + a <= t) {
        dp[i + a][0] = true;
      }
      if (i + b <= t) {
        dp[i + b][0] = true;
      }
      ans = max(ans, i);
    }
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
