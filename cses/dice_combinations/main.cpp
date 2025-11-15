#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

ui MOD = 1e9 + 7;

void solve() {
  ui n;
  cin >> n;
  vector<int> dp(n + 1, 0);
  for (size_t i = 1; i <= 6; ++i) {
    dp[i] = 1;
  }
  for (size_t i = 2; i <= n; ++i) {
    ui partial = 0;
    for (int j = 1; j <= min(6, (int)i); ++j) {
      partial = (partial + dp[i - j]) % MOD;
    }
    dp[i] = (dp[i] + partial) % MOD;
  }
  cout << dp[n] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
