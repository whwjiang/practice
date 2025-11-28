#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ifstream read("snakes.in");

  int n, K;
  read >> n >> K;
  vector<int> snakes(n + 1, 0);
  int used = 0;
  for (int i = 1; i <= n; ++i) {
    read >> snakes[i];
    used += snakes[i];
  }
  vector<vector<int>> dp(n + 1, vector<int>(K + 1, 0));

  int maxUp = snakes[1];
  for (int i = 1; i <= n; ++i) {
    maxUp = max(maxUp, snakes[i]);
    dp[i][0] = maxUp * i;
    for (int k = 1; k <= K; k++) {
      dp[i][k] = INT_MAX;
      int maxDown = snakes[i];
      for (int c = i; c >= 0; --c) {
        dp[i][k] = min(dp[i][k], dp[c][k - 1] + (maxDown * (i - c)));
        maxDown = max(maxDown, snakes[c]);
      }
    }
  }
  ofstream("snakes.out") << dp[n][K] - used << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}