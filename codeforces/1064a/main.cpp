#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  char last = s[n - 1];
  int ans = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (s[i] != last) {
      ans++;
    }
  }
  cout << ans << endl;
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
