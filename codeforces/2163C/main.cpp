#include <bits/stdc++.h>
#include <bits/basic_string.h>
using namespace std;

/*
Problem Link: https://codeforces.com/problemset/problem/2163/C
The problem solving process required you to make two important observations:

1. If (l, r) is good then (l, r + 1) is good -> fixing l, we need to
   find the first r that allows us to find a down-right path
2. Increasing l to l + 1 only decreases the number of activated cells,
   so when we increase l, we do not have to decrease r to find more solutions
  
Then, in order to determine whether a down-right path exists, we find the first
index in the top row with a 0, and then the last index in the bottom row with a 0.
Call them a and b respectively. If a - 1 > b, then there must be a path

E.g.: 
1 1 0 0 0 -> a = 2
0 0 1 1 1 -> b = 1, a - 1 = b -> no path

1 1 1 0 0 -> a = 3
0 0 1 1 1 -> b = 2, a - 1 > = -> there is a path

*/

#define int long long

void solve() {
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> pos(2 * n + 1);
  array<set<int>, 2> st;
  st[0].insert(INT_MAX);
  st[1].insert(INT_MIN);
  vector<vector<int>> a(2, vector<int>(n));
  for (int i = 0; i < n; ++i) {
    cin >> a[0][i];
    st[0].insert(i);
  }
  for (int i = 0; i < n; ++i) {
    cin >> a[1][i];
    st[1].insert(i);
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n; ++j) {
      pos[a[i][j]].push_back({i, j});
    }
  }

  auto activate = [&](int val) {
    for (auto [i, j] : pos[val]) {
      st[i].erase(j);
    }
  };

  auto deactivate = [&](int val) {
    for (auto [i, j] : pos[val]) {
      st[i].insert(j);
    }
  };

  auto check = [&]() {
    if (st[0].contains(0)) {
      return false;
    }
    if (st[1].contains(n - 1)) {
      return false;
    }
    if (*st[0].begin() - 1 <= *st[1].rbegin()) {
      return false;
    }
    return true;
  };


  int ans = 0;
  int r = 0;
  for (int l = 1; l <= 2 * n; ++l) {
    while (r + 1 <= 2 * n && !check()) {
      activate(++r);
    }
    if (!check()) {
      break;
    }
    ans += 2 * n - r + 1;
    deactivate(l);
  }
  cout << ans << endl;
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
