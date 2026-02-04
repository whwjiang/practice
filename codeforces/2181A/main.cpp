#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/contest/2181/problem/A
Key Insight: Binary search

Solution:
Just do binary search on the feasible interval. note that for lower bound style
b-search, the answer is in the lower bound (r)

*/

void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> words(n);
  array<int, 26> tot{0};
  array<int, 26> req{0};
  array<int, 26> cur{0};
  for (int i = 0; i < n; ++i) {
    cin >> words[i];
    for (const auto &c : words[i]) {
      int ind = c - 'A';
      tot[ind] += m;
      req[ind]++;
    }
  }
  auto feasible = [&](int k) {
    for (int i = 0; i < 26; ++i) {
      if (cur[i] != 0 && tot[i] - (k * req[i]) < cur[i]) {
        return false;
      }
    }
    return true;
  };
  for (const auto &w : words) {
    // form cur and req
    for (const auto &c : w) {
      int ind = c - 'A';
      req[ind]--;
      cur[ind]++;
      tot[ind] -= m;
    }
    int r = 0, l = m;
    while (r < l) {
      int mid = (r + l) / 2;
      if (feasible(mid)) {
        r = mid + 1;
      } else {
        l = mid;
      }
    }
    cout << r - 1 << ' ';
    // add cur back to req
    for (const auto &c : w) {
      int ind = c - 'A';
      req[ind]++;
      cur[ind]--;
      tot[ind] += m;
    }
  }
  cout << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
