#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  freopen("runaway.in", "r", stdin);
  freopen("runaway.out", "w", stdout);
  int n;
  ll L;
  cin >> n >> L;
  int P = 32 - __builtin_clz(n);
  vector<vector<int>> up(n, vector<int>(P, -1));
  vector<vector<ll>> upl(n, vector<ll>(P, 0));
  vector<vector<int>> adj(n);
  for (auto i = 1; i < n; ++i) {
    int parent;
    ll length;
    cin >> parent >> length;
    up[i][0] = --parent;
    upl[i][0] = length;
    adj[parent].push_back(i);
  }
  
  up[0][0] = 0;
  for (auto p = 1; p < P; ++p) {
    for (auto i = 0; i < n; ++i) {
      if (up[i][p - 1] != -1) {
        up[i][p] = up[up[i][p - 1]][p - 1];
        upl[i][p] = upl[i][p - 1] + upl[up[i][p - 1]][p - 1];
      }
    }
  }
  vector<int> count(n, 1);
  // find the node that is >= L from a given node
  for (auto i = 0; i < n; ++i) {
    ll dist{0};
    int cur = i;
    for (int p = P - 1; p >= 0; --p) {
      if (dist + upl[cur][p] <= L) {
        dist += upl[cur][p];
        cur = up[cur][p];
      }
    }
    if (cur > 0) {
      count[up[cur][0]]--;
    }
  }

  function<void(int)> dfs = [&](int cur) {
    for (auto i : adj[cur]) {
      dfs(i);
      count[cur] += count[i];
    }
  };
  dfs(0);

  for (auto i = 0; i < n; ++i) {
    cout << count[i] << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
