#include <bits/stdc++.h>
using namespace std;

using ll = long long;
/*
Problem Link: https://codeforces.com/problemset/problem/2181/M


*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--) {
    string x, y;
    cin >> x >> y;
    size_t n = x.size();
    vector<array<int, 2>> dp(n + 1);
    dp[0][0] = 0;
    dp[0][1] = 1e9;
    for (int i = 1; i <= (int)n; ++i) {
      int bit = x[i - 1] - '0';
      int par = y[i - 1] - '0';
      for (int p = 0; p <= 1; ++p) {
        dp[i][p] = min(dp[i - 1][p] + (bit != 0) + (par != p),
                       dp[i - 1][p ^ 1] + (bit != 1) + (par != p));
      }
    }
    printf("%d\n", min(dp[n][0], dp[n][1]));
  }
}
