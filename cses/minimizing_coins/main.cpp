#include <bits/stdc++.h>
#include <limits>
using namespace std;

using ll = long long;
using ui = unsigned int;
constexpr int INF = std::numeric_limits<int>::max() / 2;

void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (auto i = 0; i < n; ++i) {
    cin >> coins[i];
  }
  std::sort(coins.begin(), coins.end());
  int dp[1000001];
  for (int i = 0; i <= x; ++i) {
    dp[i] = INF;
  }
  dp[0] = 0;
  for (auto i = 0; i <= x; ++i) {
    for (const auto &c : coins) {
      if (i + c <= x && dp[i] != INF) {
        dp[i + c] = min(dp[i + c], dp[i] + 1);
      }
    }
  }
  cout << ((dp[x] == INF) ? -1 : dp[x]) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
