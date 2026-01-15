#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> h(n);
  vector<int> s(n);
  for (auto i = 0; i < n; ++i) {
    cin >> h[i];
  }
  for (auto i = 0; i < n; ++i) {
    cin >> s[i];
  }
  vector<vector<int>> dp(n + 1, vector<int>(x + 1, INT_MIN));
  dp[0][0] = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= x; ++j) {
      if (dp[i][j] == INT_MIN) {
        continue;
      }
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
      if (h[i] + j <= x) {
        dp[i + 1][h[i] + j] = max(dp[i + 1][h[i] + j], dp[i][j] + s[i]);
      }
    }
  }
  int ans = 0;
  for (int j = 0; j <= x; ++j) {
    ans = max(ans, dp[n][j]);
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
