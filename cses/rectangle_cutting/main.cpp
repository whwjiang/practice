#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

int DEFAULT = numeric_limits<int>::max();

void solve() {
  ui a, b;
  cin >> a >> b;
  int dp[501][501];
  memset(dp, 0, sizeof(dp));
  for (size_t i = 0; i <= a; ++i) {
    for (size_t j = 0; j <= b; ++j) {
      if (i != j) {
        int res = DEFAULT;
        for (size_t k = 1; k < i; ++k) {
          res = min(res, dp[k][j] + dp[i - k][j] + 1);
        }
        for (size_t k = 1; k < j; ++k) {
          res = min(res, dp[i][k] + dp[i][j - k] + 1);
        }
        dp[i][j] = res;
      }
    }
  }
  cout << dp[a][b] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
