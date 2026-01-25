#include <bits/stdc++.h>
#include <climits>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int S, n;
  cin >> S >> n;
  map<int, vector<pair<int, int>>> by_weight;
  for (auto i = 0; i < n; ++i) {
    int v, w, k;
    cin >> v >> w >> k;
    if (k == 0 || w > S) {
      continue;
    }
    by_weight[w].push_back({v, k});
  }
  vector<vector<ll>> dp(by_weight.size() + 1, vector<ll>(S + 1, LLONG_MIN));
  dp[0][0] = 0;
  int i = 1;
  for (auto &[w, items] : by_weight) {
    sort(items.begin(), items.end(), std::greater<pair<int, int>>());
    for (int j = 0; j <= S; ++j) {
      dp[i][j] = dp[i - 1][j];
      size_t cur_item = 0;
      int cur_used = 0;
      int n_items = 0;
      ll value = 0;
      while ((n_items + 1) * w <= j && cur_item < items.size()) {
        n_items++;
        value += items[cur_item].first;
        if (dp[i - 1][j - n_items * w] != LLONG_MIN) {
          dp[i][j] = max(dp[i][j], dp[i - 1][j - n_items * w] + value);
        }
        cur_used++;
        if (cur_used == items[cur_item].second) {
          cur_item++;
          cur_used = 0;
        }
      }
    }
    ++i;
  }
  ll ans = 0;
  for (auto j = 0; j <= S; ++j) {
    ans = max(ans, dp[by_weight.size()][j]);
  }
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
