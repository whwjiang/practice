#include <bits/stdc++.h>
using namespace std;
#define int long long

/*
Problem Link: https://codeforces.com/problemset/problem/2195/B
Key Insight: separate operations into classes

Solution:
I think the key to this problem is to realize that the single operation you do
constrains what you can do: you can only swap a_i and a_{2i} freely. This
implies that there are "classes" which you can swap freely:

1. a1, a2, a4, a8, ...
2. a3, a6, a12, ...
3. a5, a10, a20, ...
4. a7, a14, a28, ...

This leads us to a solution: for each class, do bubble sort. If at the end the
array is sorted, then it is sortable (duh).

*/

void solve() {
  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; i += 2) {
    for (int j = i; j <= n; j *= 2) {
      for (int k = i * 2; k <= n; k *= 2) {
        if (a[k / 2] > a[k]) {
          swap(a[k / 2], a[k]);
        }
      }
    }
  }

  cout << (is_sorted(a.begin(), a.end()) ? "YES" : "NO") << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;
  while (t--)
    solve();
}
