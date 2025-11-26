#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n, m;
  cin >> n >> m;
  // dp[i]: max num of cities from city 1 to city i
  // dp[1] = 1
  // dp[j] = max_{j \in adj[i]} dp[i] + 1

  vector<vector<int>> adj(n);
  vector<vector<int>> back(n);
  vector<int> indeg(n, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    back[b].push_back(a);
    indeg[b]++;
  }
  deque<int> q;
  for (int i = 0; i < n; ++i) {
    if (indeg[i] == 0) {
      q.push_back(i);
    }
  }
  vector<int> sorted;
  sorted.reserve(n);
  while (!q.empty()) {
    int cur = q.back();
    q.pop_back();
    sorted.push_back(cur);
    for (const auto &next : adj[cur]) {
      if (--indeg[next] == 0) {
        q.push_back(next);
      }
    }
  }

  vector<pair<int, int>> dp(n, {INT_MIN, -1});
  dp[0] = {1, 0};
  for (int i = 0; i < (int)sorted.size(); ++i) {
    int cur = sorted[i];
    for (const auto &prev : back[cur]) {
      if (dp[cur].first < dp[prev].first + 1) {
        dp[cur] = {dp[prev].first + 1, prev};
      }
    }
  }

  int len = dp[n - 1].first;
  if (len <= 0) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  vector<int> ans;
  int cur = n - 1;
  for (int i = len - 1; i >= 0; --i) {
    ans.push_back(cur + 1);
    cur = dp[cur].second;
  }
  cout << len << endl;
  reverse(ans.begin(), ans.end());
  ranges::for_each(ans, [](const auto &num) { cout << num << ' '; });
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
