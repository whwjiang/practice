#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/contest/2184/problem/E
Key Insight: you can use a DSU to record information about subarrays

Solution:
First note that if a subarray satisfies being k1-exquisite, then it is
k2-exquisite for all k2 < k1. Also note that if a subarray is length m, then its
contribution to the number of subarrays that are k-exquisite is exactly equal to
(m * (m - 1)) / 2. This points us in the direction of an algorithm:

1. Record all adjacent pairwise differences
2a. For each k from n - 1 to 1, unite indices whose pairwise difference is equal
to k using a DSU
2b. Count the contribution of this subarray to the answer for k
*/

struct DSU {
  DSU(int n) : parent(n), rank(n, 1), sz(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  int find(int x) {
    if (parent[x] == x) {
      return x;
    }
    return parent[x] = find(parent[x]);
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return;
    }
    if (rank[a] < rank[b]) {
      swap(a, b);
    }
    parent[b] = a;
    if (rank[a] == rank[b]) {
      ++rank[a];
    }
    sz[a] += sz[b];
  }

  int count(int x) {
    x = find(x);
    return (sz[x] * (sz[x] - 1)) / 2;
  }

  vector<int> parent;
  vector<int> rank;
  vector<int> sz;
};

void solve() {
  int n;
  cin >> n;

  map<int, vector<int>> m;
  int prev;
  for (int i = 0; i < n; ++i) {
    int v;
    cin >> v;
    if (i > 0) {
      m[abs(v - prev)].push_back(i);
    }
    prev = v;
  }

  DSU dsu(n);

  vector<int> ans;
  ans.reserve(n - 1);
  int cur = 0;
  for (int k = n - 1; k > 0; --k) {
    for (const auto &i : m[k]) {
      cur -= dsu.count(i);
      cur -= dsu.count(i - 1);
      dsu.unite(i, i - 1);
      cur += dsu.count(i);
    }
    ans.push_back(cur);
  }
  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    cout << *it << ' ';
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
}
