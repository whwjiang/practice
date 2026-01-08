#include <bits/stdc++.h>
#include <climits>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);
  int n, W;
  cin >> n >> W;
  vector<int> w(n);
  vector<int> t(n);
  for (auto i = 0; i < n; ++i) {
    cin >> w[i] >> t[i];
  }
  // dp[i] : the maximum possible score with weight capped at i
  vector<ll> dp(1e3 + 1);
  auto works = [&](ll y) {
    std::fill(dp.begin(), dp.end(), LLONG_MIN);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = W; j >= 0; --j) {
        if (dp[j] == LLONG_MIN) {
          continue;
        }
        int k = min(W, j + w[i]);
        dp[k] = max(dp[k], dp[j] + 1000 * t[i] - y * w[i]);
      }
    }
    return dp[W] >= 0;
  };
  ll ans = 0;
  for (ll dif = 1e6; dif > 0; dif /= 2) {
    while (works(ans + dif)) {
      ans += dif;
    }
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
