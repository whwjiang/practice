#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ui a, b, n;
  cin >> a >> b >> n;
  if (a == b || (static_cast<float>(a) / static_cast<float>(n)) >= static_cast<float>(b)) {
    cout << 1 << endl;
  } else {
    cout << 2 << endl;
  }
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
