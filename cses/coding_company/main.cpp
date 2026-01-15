#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;
constexpr int MOD = 1e9 + 7;
constexpr int K = 5e3;

void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> t(n);
  for (auto i = 0; i < n; ++i) {
    cin >> t[i];
  }
  sort(t.begin(), t.end());
  vector<vector<ll>> dp1(n + 1, vector<ll>(x + K + 1));
  vector<vector<ll>> dp2(n + 1, vector<ll>(x + K + 1));
  dp1[0][K] = 1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= n - i; ++j) {
      for (int k = 0; k <= x + K; ++k) {
        if (!dp1[j][k]) {
          continue;
        }
        dp2[j][k] += dp1[j][k];
        dp2[j][k] %= MOD;
        if (j && k + t[i] <= x + K) {
          dp2[j - 1][k + t[i]] += dp1[j][k] * j;
          dp2[j - 1][k + t[i]] %= MOD;
        }
        if (j + 1 <= n - (i + 1) && k >= t[i]) {
          dp2[j + 1][k - t[i]] += dp1[j][k];
          dp2[j + 1][k - t[i]] %= MOD;
        }
        if (j <= n - (i + 1)) {
          dp2[j][k] += dp1[j][k] * j;
          dp2[j][k] %= MOD;
        }
      }
    }
    for (int j = 0; j <= n - (i + 1); ++j) {
      for (int k = 0; k <= x + K; ++k) {
        dp1[j][k] = dp2[j][k];
        dp2[j][k] = 0;
      }
    }
  }

  ll ans = 0;
  for (int k = K; k <= x + K; ++k) {
    ans += dp1[0][k];
    ans %= MOD;
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
