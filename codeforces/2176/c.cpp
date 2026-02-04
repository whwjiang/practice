#include <bits/stdc++.h>
using namespace std;

#define int long long

/*
Problem Link: https://codeforces.com/problemset/problem/2176/C
Key Insight: Treating the k is even and k is odd cases separately

Solution:
First recall e + o = o, e + e = e, o + o = e. This gives us a hint towards
solving: for k = 1, the best we can do is take the largest value odd coin, and
for k = 2, the best we can do is take the largest even coin and the largest odd
coin. From there, we can only improve these two base cases if there are more
than two even coins left. Let k be the current number of coins we have to take.
If the solution at k - 2 leaves two even coins, then our answer at k goes up by
the value of the two largest even coins. Otherwise, if it leaves two odd coins,
then we our solution does not change, because we could take those two coins at
the beginning and use our solution from k - 2. Otherwise, we are in a position
where we have to take an even and an odd, in which case our solution for k is 0.

*/

void solve() {
  int n;
  cin >> n;
  vector<vector<int>> odd(2);
  vector<vector<int>> even(2);
  for (int i = 0; i < n; ++i) {
    int cur;
    cin >> cur;
    if (cur & 1) {
      odd[0].push_back(cur);
      odd[1].push_back(cur);
    } else {
      even[0].push_back(cur);
      even[1].push_back(cur);
    }
  }
  sort(odd[0].begin(), odd[0].end());
  sort(odd[1].begin(), odd[1].end());
  sort(even[0].begin(), even[0].end());
  sort(even[1].begin(), even[1].end());
  vector<int> ans(n + 1);
  for (int k = 1; k <= n; ++k) {
    int par = k & 1;
    if (k == 1) {
      if (odd[par].empty()) {
        ans[k] = 0;
      } else {
        ans[k] = odd[par].back();
        odd[1].pop_back();
      }
    } else if (k == 2) {
      if (odd[par].empty() || even[par].empty()) {
        ans[k] = 0;
      } else {
        ans[k] = odd[par].back() + even[par].back();
        odd[par].pop_back();
        even[par].pop_back();
      }
    } else {
      int best = ans[k - 2];
      if (even[par].size() >= 2) {
        best += even[par].back();
        even[par].pop_back();
        best = (best & 1) ? best : 0;
        best += even[par].back();
        even[par].pop_back();
        best = (best & 1) ? best : 0;
      } else if (odd[par].size() >= 2) {
        odd[par].pop_back();
        odd[par].pop_back();
      } else {
        best = 0;
        // they both have to be one, or else we wouldn't be in the loop still
        odd[par].pop_back();
        even[par].pop_back();
      }
      ans[k] = best;
    }

    cout << ans[k] << ' ';
  }
  cout << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
  return 0;
}
