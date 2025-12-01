#include <bits/stdc++.h>
using namespace std;

int n, Q, L;
vector<vector<int>> adjList;
vector<vector<int>> up;
vector<int> depth;

void dfs(int cur, int parent, int dep) {
  up[cur][0] = parent;
  depth[cur] = dep;
  for (const auto &next : adjList[cur]) {
    if (next != parent) {
      dfs(next, cur, dep + 1);
    }
  }
}

int lift(int node, int k) {
  for (int p = 0; p < L; p++) {
    if (node != -1 && ((k >> p) & 1)) {
      node = up[node][p];
    }
  }
  return node;
}
int lca(int a, int b) {
  a = lift(a, depth[a] - min(depth[a], depth[b]));
  b = lift(b, depth[b] - min(depth[a], depth[b]));
  if (a == b) {
    return a;
  }
  for (int p = L - 1; p >= 0; --p) {
    if (up[a][p] != up[b][p]) {
      a = up[a][p], b = up[b][p];
    }
  }
  return up[a][0];
}
int distance(int a, int b) {
  return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

void solve() {
  cin >> n >> Q;
  L = 32 - __builtin_clz(n);
  adjList.assign(n, vector<int>{});
  up.assign(n, vector<int>(L, -1));
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    adjList[--a].push_back(--b);
    adjList[b].push_back(a);
  }
  depth.assign(n, 0);
  dfs(0, -1, 0);
  // fill out binary lifting table
  for (int p = 1; p < L; ++p) {
    for (int i = 0; i < n; ++i) {
      if (up[i][p - 1] != -1) {
        up[i][p] = up[up[i][p - 1]][p - 1];
      }
    }
  }
  // main loop
  for (int q = 0; q < Q; q++) {
    int a, b;
    cin >> a >> b;
    cout << distance(--a, --b) << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
