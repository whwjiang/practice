#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);
  vector<int> indeg(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    indeg[b]++;
  }
  deque<int> q;
  for (int i = 1; i <= n; ++i) {
    if (indeg[i] == 0) {
      q.push_back(i);
    }
  }
  vector<int> ans;
  while (!q.empty()) {
    int cur = q.back();
    q.pop_back();
    ans.push_back(cur);
    for (const auto next : adj[cur]) {
      indeg[next]--;
      if (indeg[next] == 0) {
        q.push_back(next);
      }
    }
  }
  if ((int)ans.size() != n) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  ranges::for_each(as_const(ans), [](const auto &num) { cout << num << ' '; });
  // cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
