#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ui n;
  cin >> n;
  vector<vector<char>> grid(n, vector<char>(n));
  for (size_t i = 0; i < n * n; ++i) {
    cin >> grid[i / n][i % n];
  }
  vector<string> prev(n);
  vector<string> cur(n);
  prev[0] = grid[0][0];
  for (size_t i = 1; i < n; ++i) {
    prev[i] = prev[i - 1] + grid[0][i];
  }
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      cur[j] = prev[j];
      if (j > 0) {
        cur[j] = min(cur[j], cur[j - 1]);
      }
      cur[j].push_back(grid[i][j]);
    }
    swap(prev, cur);
    cur.assign(n, {});
  }
  cout << prev[n - 1] << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
