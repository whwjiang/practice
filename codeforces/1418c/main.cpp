#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
  size_t n;
  cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> a[i];
  }
  if (n <= 2) {
    cout << a[0] << endl;
    return;
  }
  vector<int> you(n, INT_MAX);
  vector<int> me(n, INT_MAX);
  you[n - 1] = a[n - 1];
  me[n - 1] = 0;
  you[n - 2] = a[n - 2];
  me[n - 2] = 0;
  for (int i = (int)n - 3; i >= 0; --i) {
    you[i] = min(a[i] + me[i + 1], a[i] + a[i + 1] + me[i + 2]);
    me[i] = min(you[i + 1], you[i + 2]);
  }
  cout << you[0] << endl;
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
