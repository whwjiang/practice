#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int W, H, n;
  cin >> W >> H >> n;
  vector<int> w(n);
  vector<int> h(n);
  for (auto i = 0; i < n; ++i) {
    cin >> w[i] >> h[i];
  }
  vector<vector<int>> dp(W + 1, vector<int>(H + 1, 0));
  for (int i = 1; i <= W; ++i) {
    for (int j = 1; j <= H; ++j) {
      dp[i][j] = i * j;
    }
  }
  for (int i = 0; i < n; ++i) {
    dp[w[i]][h[i]] = 0;
  }
  for (int i = 1; i <= W; ++i) {
    for (int j = 1; j <= H; ++j) {
      // horizontal cut
      for (int c = 1; c <= i; ++c) {
        dp[i][j] = min(dp[i][j], dp[i - c][j] + dp[c][j]);
      }
      // vertical cut
      for (int c = 1; c <= j; ++c) {
        dp[i][j] = min(dp[i][j], dp[i][j - c] + dp[i][c]);
      }
    }
  }
  cout << dp[W][H] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
