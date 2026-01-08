#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n;
  cin >> n;
  vector<int> coins(n);
  int S = 0;
  for (int i = 0; i < n; ++i) {
    cin >> coins[i];
    S += coins[i];
  }

  vector<char> dp(S + 1, 0);
  dp[0] = 1;

  for (int c : coins) {
    for (int s = S; s >= c; --s) {
      dp[s] |= dp[s - c];
    }
  }

  vector<int> ans;
  for (int s = 1; s <= S; ++s) {
    if (dp[s])
      ans.push_back(s);
  }

  cout << ans.size() << '\n';
  for (int x : ans)
    cout << x << ' ';
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
