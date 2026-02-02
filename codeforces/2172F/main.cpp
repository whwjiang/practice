#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
Problem Link: https://codeforces.com/problemset/problem/2172/F
There is a way to solve this without actually creating the MST. We need to make
two key observations:

1. The edge from the first node to the last node is always going to be used, as
it has the lowest possible range GCD out of all possible pairs (l, r)

2. Given a pair (l, r) s.t. 1 < l < r < n, it is always better to add the either
the edge (1, l) or the edge (r, n). This is because the operations are
equivalent to building an MST, but the latter two operations are always going to
result in a lower range GCD

So we precompute the prefix and suffix GCDs, and at every i, add the min of the
range gcd from 0 to i, or the range gcd from i to n - 1.
*/

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  vector<int> pre(n + 1), suf(n + 1);

  // pre[i] = gcd(a[0..i-1])
  for (int i = 1; i <= n; ++i) {
    pre[i] = gcd(pre[i - 1], a[i - 1]);
  }

  // suf[i] = gcd(a[i..n-1])
  for (int i = n - 1; i >= 0; --i) {
    suf[i] = gcd(suf[i + 1], a[i]);
  }

  ll ans = 0;
  // split between i-1 and i
  for (int i = 0; i < n - 1; ++i) {
    ans += min(pre[i + 1], suf[i]);
  }

  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
