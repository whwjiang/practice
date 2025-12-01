#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  int n, Q;
  cin >> n >> Q;
  int L = 32 - __builtin_clz(n);
  vector<vector<int>> up(n + 1, vector<int>(L, -1));
  for (int i = 1; i < n; ++i) {
    int parent;
    cin >> parent;
    up[i][0] = --parent;
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
      if (node != -1 && ((k >> p) & 1)) {
        node = up[node][p];
      }
    }
    return node;
  };
  for (int q = 0; q < Q; ++q) {
    int node, k;
    cin >> node >> k;
    node--;
    int res = lift(node, k);
    cout << ((res == -1) ? -1 : res + 1) << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
