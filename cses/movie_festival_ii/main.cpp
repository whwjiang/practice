#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ui n, k;
  cin >> n >> k;
  vector<pair<int, int>> movies(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> movies[i].first >> movies[i].second;
  }
  sort(movies.begin(), movies.end());
  ui ans = 0;
  multiset<int> watching;
  for (const auto &[a, b] : movies) {
    if (watching.size() < k) {
      watching.insert(b);
      continue;
    }
    auto it = watching.lower_bound(a);
    if (a == *it) {
      ans++;
      watching.erase(it);
      watching.insert(b);
    } else if (it != watching.begin()) {
      it = prev(it);
      ans++;
      watching.erase(it);
      watching.insert(b);
    } else {
      it = prev(watching.end());
      if (b < *it) {
        watching.erase(it);
        watching.insert(b);
      }
    }
  };
  // cout << ans << endl;
  cout << ans + watching.size() << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
