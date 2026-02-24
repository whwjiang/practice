
#include <bits/stdc++.h>
using namespace std;

// #define int long long
/*
Problem Link: https://codeforces.com/contest/2195/problem/C
Key Insight: realizing that this was a dp problem

Solution:
Let dp[i][j] be the number of ops required to make a[0..i] a valid dice roll
sequence given a[i] = j. The base case is dp[0][j] = 0 when a[0] == j, and 1
otherwise. Then we can pretty easily go through the dp array, iterating on every
possible pair of dice rolls j and k. If j and k are not compatible, we do not
consider them. Otherwise, we choose between keeping our best answer, or matching
j and k. There is no cost if j == vals[i], otherwise the cost is 1 (the cost of
an operation, essentially).
*/

void solve() {
  int n;
  cin >> n;
  vector<int> vals(n);
  for (int i = 0; i < n; ++i) {
    cin >> vals[i];
  }
  auto compat = [](int a, int b) {
    int mn = min(a, b);
    int mx = max(a, b);
    return a != b && ((7 - mn) != mx);
  };
  vector<vector<int>> dp(n, vector<int>(7, 1e9));
  for (int i = 1; i <= 6; ++i) {
    dp[0][i] = (i != vals[0]);
  }

  for (int i = 1; i < n; ++i) {
    for (int j = 1; j <= 6; ++j) {
      for (int k = 1; k <= 6; ++k) {
        if (!compat(j, k)) {
          continue;
        }
        dp[i][j] = min(dp[i][j], dp[i - 1][k] + !(j == vals[i]));
      }
    }
  }

  int ans = INT_MAX;
  for (int i = 1; i <= 6; ++i) {
    ans = min(ans, dp[n - 1][i]);
  }
  cout << ans << endl;
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
