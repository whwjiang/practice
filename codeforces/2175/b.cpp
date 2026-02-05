#include <bits/stdc++.h>
using namespace std;

using ll = long long;
/*
Problem Link: https://codeforces.com/problemset/problem/2175/B
Key Insight: prefix sums, properties of XOR

Solution:
When talking about XOR of a subsegment, it's usually useful to think about
prefix XORs. Then, if bi=a1⊕a2⊕…⊕ai is the array or prefix XORs, the subsegment
XOR f is simply f(x,y)=b_y⊕b_{x−1} . That means, for f(l,r) to be zero, bl−1 has to
be equal to br , while all other values of b should be distinct. The easiest
construction is then bi=i , with the exception that br=l−1 . The array a can be
then reconstructed as ai=bi⊕bi−1
.
*/

void solve() {
  int n, l, r;
  cin >> n >> l >> r;
  vector<int> pre(n + 1, 1);
  std::iota(pre.begin(), pre.end(), 0);
  pre[r] = l - 1;
  for (int i = 1; i <= n; ++i) {
    cout << (pre[i] ^ pre[i - 1]) << ' ';
  }
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
}
