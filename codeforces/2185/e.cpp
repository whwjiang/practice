#include <bits/stdc++.h>
using namespace std;

/*
Problem Link: https://codeforces.com/problemset/problem/2185/E
Key Insight: We don't care about the actual positions of the robots, just their
current delta

Solution:
At first, this problem seems untenable because it seems you have to keep track
of every single robot for every single move. However, there are two key
observations:

1. Because a robot immediately dies when it hits spikes, we only care about the
spikes immediately to the left and right of it
2. As a result of 1, we only need to check the relative distance we are at, and
count how many robots die at this offset

*/

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> robots(n);
  vector<int> spikes(m);
  string instr;

  for (int i = 0; i < n; ++i) {
    cin >> robots[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> spikes[i];
  }
  cin >> instr;

  vector<int> dead(n, 0);
  map<int, vector<int>> deathspot;
  sort(spikes.begin(), spikes.end());

  for (int i = 0; i < n; ++i) {
    auto robot = robots[i];
    // get the closest spike left and right of r
    if (spikes[0] < robot) {
      int left_dist =
          robot - (*(lower_bound(spikes.begin(), spikes.end(), robot) - 1));
      deathspot[-left_dist].push_back(i);
      // cout << -left_dist << ' ';
    }
    if (spikes[m - 1] > robot) {
      int right_dist =
          *lower_bound(spikes.begin(), spikes.end(), robot) - robot;
      deathspot[right_dist].push_back(i);
      // cout << right_dist << ' ';
    }
  }
  int cur = 0;
  int ans = n;
  for (const auto &c : instr) {
    if (c == 'L') {
      --cur;
    } else {
      ++cur;
    }
    for (auto i : deathspot[cur]) {
      if (!dead[i]) {
        ans--;
      }
      dead[i] = 1;
    }
    deathspot[cur].clear();
    cout << ans << ' ';
  }
  cout << endl;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--) {
    solve();
  }
}
