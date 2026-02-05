#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2193/F
Key Insight: The problem limitations reduce the amount of state you have to keep
track of

Solution:
When I first approached this problem, I naturally gravitated towards DP because
I quickly made the observation that because you can't go in the direction of
negative x, each set of houses at the same x would have to be processed
together, before moving on to the next level set. However, I got tripped up
because I was trying to think of ways to process the homes in a single set in
some order, which naively is impossible to do in non-exponential time. That's
when I made this key observation:

1. Coming from the previous level set, the only optimal way to go through all
houses in a level set is to either go directly from top to bottom or vice-versa

This means that at every DP state, we need to decide if it is shorter to come
from the top and go down, or vice versa. So the only DP state we need to track
is the current level set we are on, and whether we came from the bottom or the
top.

*/

void solve() {
  int n, ax, ay, bx, by;
  cin >> n >> ax >> ay >> bx >> by;
  vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> y[i];
  }
  map<int, vector<int>> m;
  for (int i = 0; i < n; ++i) {
    m[x[i]].push_back(y[i]);
  }
  m[ax].push_back(ay);
  m[bx].push_back(by);

  auto dist = [&](int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
  };

  vector<vector<int>> dp(m.size() + 1, vector<int>(2, 0));
  int i = 0, prev_x = ax, prev_bot = ay, prev_top = ay;
  for (auto &[cur_x, ys] : m) {
    if (cur_x == ax) {
      continue;
    }
    ++i;
    sort(ys.begin(), ys.end());
    int bot = ys.front();
    int top = ys.back();
    int len = top - bot;
    // cout << cur_x << ' ' << bot << ' ' << top << ' ' << len << endl;
    dp[i][0] = len + min(dp[i - 1][0] + dist(prev_x, prev_top, cur_x, bot),
                         dp[i - 1][1] + dist(prev_x, prev_bot, cur_x, bot));
    dp[i][1] = len + min(dp[i - 1][0] + dist(prev_x, prev_top, cur_x, top),
                         dp[i - 1][1] + dist(prev_x, prev_bot, cur_x, top));

    prev_x = cur_x;
    prev_bot = bot;
    prev_top = top;
  }
  cout << min(dp[i][0], dp[i][1]) << endl;
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
