#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  vector<array<int, 2>> dp(1e6 + 1);
  while (t--) {
    string x, y;
    cin >> x >> y;
    size_t n = x.size();
    dp.clear();
    dp.resize(n + 1);
    if (x[0] == '0') {
      dp[0][0] = 0;
      dp[0][1] = 1;
    } else {
      dp[0][0] = 1;
      dp[0][1] = 0;
    }
    for (auto i = 1; i < (int)n; ++i) {
      bool bit = x[i] - '0';
      bool par = y[i] - '0';
      dp[i][0] = (par != 0) + min(dp[i - 1][0] + (bit != 0), dp[i - 1][1] + (bit != 1));
      dp[i][1] = (par != 1) + min(dp[i - 1][1] + (bit != 0), dp[i - 1][0] + (bit != 1));

    }
    if (n == 1) {
      printf("%d\n", dp[0][y[0] - '0']);
    } else {
      printf("%d\n", min(dp[n - 1][0], dp[n - 1][1]));

    }
  }
}
