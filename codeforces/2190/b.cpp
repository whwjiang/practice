#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2190/B1
Key Insight:

Solution:

*/

void solve() {
  int n;
  string s;
  cin >> n >> s;
  vector<int> nx(n + 1, n + 1);
  vector<int> suf(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == '(')
      nx[i] = i;
    else
      nx[i] = nx[i + 1];
    if (s[i] == '(')
      suf[i] += 1;
    suf[i] += suf[i + 1];
  }

  int ans = -1;
  for (int i = 0; i < n; i++) {
    if (s[i] == ')' and nx[i] <= n) {
      int ig = nx[i] - i;
      if (suf[nx[i] + 1] >= ig) {
        ans = max(ans, n - 2 * ig);
      }
    }
  }

  cout << ans << '\n';
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
