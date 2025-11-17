#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  size_t n;
  cin >> n;
  vector<int> nums(n);
  ll sum = 0;
  for (size_t i = 0; i < n; ++i) {
    cin >> nums[i];
    sum += (ll)nums[i];
  }
  vector<vector<ll>> dp(n, vector<ll>(n, LLONG_MIN));
  for (int i = (int)n - 1; i >= 0; --i) {
    dp[i][i] = nums[i];
    for (int j = i + 1; j < (int)n; ++j) {
      dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
    }
  }
  cout << (sum + dp[0][n - 1]) / 2 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
