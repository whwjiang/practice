#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

void solve() {
  ui n, k;
  cin >> n >> k;
  vector<pair<int, int>> movies;
  int s, e;
  for (size_t i = 0; i < n; ++i) {
    cin >> s >> e;
    movies.push_back({s, e});
  }
  sort(movies.begin(), movies.end());
  ui ans = 0;
  multiset<int> watching;
  for (const auto &[a, b] : movies) {
    // cout << a << ", " << b << endl;
    if (watching.size() < k) {
      watching.insert(b);
      continue;
    }
    auto it = watching.lower_bound(a);
    if (a == *it) {
      // cout << a << " begins after " << *it << endl;
      ans++;
      watching.erase(it);
      watching.insert(b);
    } else if (it != watching.begin()) {
      it = prev(it);
      // cout << a << " begins after " << *it << endl;
      ans++;
      watching.erase(it);
      watching.insert(b);
    } else {
      // if it ends sooner than the greatest end time, replace that one
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
