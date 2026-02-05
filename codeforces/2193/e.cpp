#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2193/E
Key Insight: approach number theory problems using the toolkit you have

Solution:
Even though it feels like number theory, it is possible to approach with dp. The
goal is effectively to find the "shortest" path to i from 1 to n using whatever
numbers appeared in the original array.

There were two tricks used in the solution:
1. We use push DP, and push the solution for dp[i] to whatever its multiples are
2. Because we are using long long and an INF well below the max for LL, adding
two INFs will not result in overflow, and we will never set the dp[j] to that
value because we take the min at each step.

*/

constexpr int INF = 1e9;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> dp(n + 1, INF);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    dp[a[i]] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      dp[j] = min(dp[j], dp[i] + dp[j / i]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << (dp[i] == INF ? -1 : dp[i]) << ' ';
  }
  cout << endl;
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
