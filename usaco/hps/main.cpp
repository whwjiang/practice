#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

bool beats(const int a, const int b) {
  return (a - b == 1) || (a == 0 && b == 2);
}

int action_to_int(const char a) {
  if (a == 'H') {
    return a - 'H';
  } else if (a == 'P') {
    return a - 'O';
  }
  return a - 'Q';
}

void solve() {
  freopen("hps.in", "r", stdin);
  freopen("hps.out", "w", stdout);
  int n, K;
  cin >> n >> K;
  vector<int> seq(n);
  for (int i = 0; i < n; ++i) {
    char a;
    cin >> a;
    seq[i] = action_to_int(a);
  }
  // dp[i][j][k]: max number of wins from 0:i given j changes and you are
  // currently playing k
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(K + 1, vector<int>(3, INT_MIN)));
  dp[0][0][0] = 0;
  dp[0][0][1] = 0;
  dp[0][0][2] = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= K; ++j) {
      for (int k = 0; k <= 2; ++k) {
        if (dp[i][j][k] == INT_MIN) {
          continue;
        }
        // printf("%d %d %d: %d\n", i, j, k, dp[i][j][k]);
        dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k] + beats(k, seq[i]));
        if (j + 1 <= K) {
          for (int alt = 0; alt <= 2; ++alt) {
            if (alt == k) {
              continue;
            }
            dp[i + 1][j + 1][alt] =
                max(dp[i + 1][j + 1][alt], dp[i][j][k] + beats(alt, seq[i]));
          }
        }
      }
    }
  }
  int ans = 0;
  for (int j = 0; j <= K; ++j) {
    for (int k = 0; k <= 2; ++k) {
      ans = max(ans, dp[n][j][k]);
    }
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
