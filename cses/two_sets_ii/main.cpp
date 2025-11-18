#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

int MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  int total = (n * (n + 1)) / 2;
  if (total & 1) {
    cout << 0 << endl;
    return;
  }
  total /= 2;
  vector<vector<int>> dp(n, vector<int>(total + 1, 0));
  dp[0][0] = 1;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= total; ++j) {
      dp[i][j] += dp[i - 1][j];
      int prev = j - i;
      if (prev >= 0) {
        dp[i][j] += dp[i - 1][prev];
      }
      dp[i][j] = dp[i][j] % MOD;
    }
  }
  cout << dp[n - 1][total] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
