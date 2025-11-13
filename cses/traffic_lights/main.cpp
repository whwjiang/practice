#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

set<int> lights;
multiset<int> dist;

void solve() {
  ui x;
  cin >> x;
  size_t n;
  cin >> n;
  lights.insert(0);
  lights.insert(x);
  dist.insert(x);
  ui cur;
  for (size_t i = 0; i < n; ++i) {
    cin >> cur;
    auto gt = lights.upper_bound(cur);
    auto lt = prev(gt);
    dist.erase(dist.find(*gt - *lt));
    dist.insert(*gt - cur);
    dist.insert(cur - *lt);
    lights.insert(cur);
    cout << *prev(dist.end()) << ' ';
  }
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
