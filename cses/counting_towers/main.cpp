#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;
constexpr int MOD = 1e9 + 7;
ll join[1000001];
ll sep[1000001];

void solve() {
  int n;
  cin >> n;
  memset(join, 0, sizeof(join));
  memset(sep, 0, sizeof(sep));
  join[0] = 1;
  sep[0] = 1;
  for (auto i = 1; i < n; ++i) {
    join[i] = 2 * join[i - 1] + sep[i - 1];
    join[i] %= MOD;
    sep[i] = 4 * sep[i - 1] + join[i - 1];
    sep[i] %= MOD;
  }
  cout << (join[n - 1] + sep[n - 1]) % MOD << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  for (auto i = 0; i < t; ++i) {
    solve();
  }
}
