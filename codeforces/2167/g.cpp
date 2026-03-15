#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link:
Key Insight:

Solution:

*/

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> c(n);

  for (int i{0}; i < n; ++i) {
    cin >> a[i];
  }

  for (int i{0}; i < n; ++i) {
    cin >> c[i];
  }
  vector<int> dp = c;
  for (int i{0}; i < n; ++i) {
    for (int j{0}; j < i; ++j) {
      if (a[j] <= a[i]) {
        dp[i] = max(dp[i], dp[j] + c[i]);
      }
    }
  }
  cout << accumulate(c.begin(), c.end(), 0) - *max_element(dp.begin(), dp.end())
       << '\n';
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
}
