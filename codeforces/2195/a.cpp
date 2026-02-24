#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  bool flag = false;
  for (int i = 0; i < n; ++i) {
    int val;
    cin >> val;
    if (val == 67) {
      flag = true;
    }
  }
  cout << (flag ? "YES" : "NO") << endl;
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
