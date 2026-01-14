#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;
constexpr int MOD = 1e9 + 7;

void solve() {
  freopen("poetry.in", "r", stdin);
  freopen("poetry.out", "w", stdout);
  int n, m, K;
  cin >> n >> m >> K;
  vector<int> s(n);
  vector<int> c(n);
  for (auto i = 0; i < n; ++i) {
    cin >> s[i] >> c[i];
  }
  unordered_map<int, ll> count;
  vector<ll> dp(K + 1, 0);
  // dp[i]: the number of ways to form a line with exactly i syllables
  dp[0] = 1;
  for (auto i = 0; i < K; ++i) {
    for (auto j = 0; j < n; ++j) {
      if (dp[i] != 0 && i + s[j] == K) {
        count[c[j]] += dp[i];
      }
      if (dp[i] != 0 && i + s[j] <= K) {
        dp[i + s[j]] += dp[i];
      }
    }
  }
  for (const auto &[rhyme, num] : count) {
    cout << rhyme << ": " << num << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
