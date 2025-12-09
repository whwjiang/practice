#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n, Q;
  cin >> n >> Q;
  int L = 32 - __builtin_clz(n);
  vector<int> depth(n, 0);
  vector<vector<int>> up(n, vector<int>(L, -1));
  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    up[i][0] = --p;
    depth[i] = 1 + depth[p];
  }
  for (int p = 1; p < L; ++p) {
    for (int i = 0; i < n; ++i) {
      if (up[i][p - 1] != -1) {
        up[i][p] = up[up[i][p - 1]][p - 1];
      }
    }
  }

  auto lift = [&](int node, int k) {
    for (int p = 0; p < L; ++p) {
      if (node == -1) {
        break;
      } else if ((k >> p) & 1) {
        node = up[node][p];
      }
    }
    return node;
  };
  auto lca = [&](int a, int b) {
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
  };
  for (int q = 0; q < Q; ++q) {
    int a, b;
    cin >> a >> b;
    cout << lca(--a, --b) + 1<< endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
