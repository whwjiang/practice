#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2169/C
Key Insight: rearranging the formula to group like terms

Solution:
Let's define Si as the sum of the first i elements in array a. When we perform
an operation on the range [l,r], the total sum changes by
(l+r)(r−l+1)−(Sr−Sl−1). This expression can be simplified to f(r)−f(l−1), where
f(x)=x2+x−Sx. So, we can iterate through the values of r, keeping track of the
minimum value of f(l) we've encountered so far (let's call it mn). Then we can
update the answer with Sn+f(r)−mn.
*/

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> pre(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    pre[i + 1] = pre[i] + a[i];
  }
  auto f = [&](int i) { return i * i + i - pre[i]; };
  int mn = f(0);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int cur = f(i);
    ans = max(ans, pre[n] + cur - mn);
    mn = min(mn, cur);
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
