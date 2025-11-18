#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ifstream read("teamwork.in");
  int n, k;
  read >> n >> k;
  vector<int> skills(n);
  for (int i = 0; i < n; ++i) {
    read >> skills[i];
  }
  vector<ll> dp(n, 0);
  for (int i = 0; i < n; ++i) {
    int cur = skills[i];
    for (int j = i; j >= max(i - k + 1, 0); j--) {
      cur = max(cur, skills[j]);
      if (j > 0) {
        dp[i] = max(dp[i], cur * (i - j + 1) + dp[j - 1]);
      } else {
        dp[i] = max(dp[i], (ll)cur * (i - j + 1));
      }
    }
  }
  ofstream("teamwork.out") << dp[n - 1] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
