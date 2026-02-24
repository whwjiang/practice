#include <bits/stdc++.h>
using namespace std;

#define int long long
/*
Problem Link: https://codeforces.com/problemset/problem/2195/F
Key Insight: First, trying to model the problem as a graph problem. Next,
using properties of functions to reduce the graph problem to something easier.

Solution:
Let's say we model the relationships between polynomials being independent from
each other as a graph, where each polynomial is a node, and we have edges
between two polynomials f and g if f(x) < g(x) for all x. Then answering this
question is essentially finding max clique membership, which is an NP-hard
problem.

The key insight is that f < g < h -> f < h, and that f < g -> !(g < f), which
implies that the relationship is a strict partial ordering. This means we are
essentially finding the longest path in the resulting directed graph. There are
a lot of ways to do this; the solution below takes the approach of doing DP to
find the longest path starting at a node i and the longest path ending at a node
i, which makes ans[i] = dp1[i] + dp2[i] - 1.

The last piece to figure out is how to determine if f < g... Using some algebra,
this amounts to finding if h(x) = g(x) - f(x) = ax^2 + bx + c > 0 for all x. If
a < 0, then surely h(x) <= 0. Otherwise if a == 0, then h(x) is a straight line
and we need to see if the slope is 0 and the y-intercept is greater than 0.
Otherwise, we need to check the determinant. If the determinant is less than 0,
then h(x) has no real roots, and we can conclude h(x) > 0.

*/

struct Quad {
  int a;
  int b;
  int c;

  Quad operator-(const Quad &other) const {
    Quad temp;
    temp.a = a - other.a;
    temp.b = b - other.b;
    temp.c = c - other.c;
    return temp;
  }
};

bool operator<(const Quad &f, const Quad &g) {
  Quad h = g - f;
  if (h.a < 0) {
    return false;
  } else if (h.a == 0) {
    return h.b == 0 && h.c > 0;
  } else {
    return h.b * h.b - 4 * h.a * h.c < 0;
  }
}

void solve() {
  int n;
  cin >> n;
  vector<Quad> q;
  q.reserve(n);
  for (int i = 0; i < n; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    q.push_back({a, b, c});
  }
  vector<vector<int>> adj1(n), adj2(n);
  vector<int> dp1(n, 1), indeg1(n), dp2(n, 1), indeg2(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (q[i] < q[j]) {
        adj1[i].push_back(j);
        indeg1[j]++;
        adj2[j].push_back(i);
        indeg2[i]++;
      }
    }
  }

  deque<int> dq;
  for (int i = 0; i < n; ++i) {
    if (indeg1[i] == 0) {
      dq.push_back(i);
    }
  }
  while (!dq.empty()) {
    int cur = dq.front();
    dq.pop_front();
    for (int next : adj1[cur]) {
      indeg1[next]--;
      dp1[next] = max(dp1[next], 1 + dp1[cur]);
      if (indeg1[next] == 0) {
        dq.push_back(next);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    if (indeg2[i] == 0) {
      dq.push_back(i);
    }
  }
  while (!dq.empty()) {
    int cur = dq.front();
    dq.pop_front();
    for (int next : adj2[cur]) {
      indeg2[next]--;
      dp2[next] = max(dp2[next], 1 + dp2[cur]);
      if (indeg2[next] == 0) {
        dq.push_back(next);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << dp1[i] + dp2[i] - 1 << " \n"[i + 1 == n];
  }
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
