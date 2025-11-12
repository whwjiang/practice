#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

map<ui, unordered_set<ui>> dists;
map<ui, map<ui, unordered_set<ui>>::iterator> poles;

void insert(ui pos, ui dist) {
  auto [it, _] = dists.try_emplace(dist, unordered_set<ui>());
  it->second.insert(pos);
  poles[pos] = it;
}

void solve() {
  ui x;
  cin >> x;
  size_t n;
  cin >> n;
  insert(x, x);
  ui cur;
  for (size_t i = 0; i < n; ++i) {
    cin >> cur;
    auto gt = poles.upper_bound(cur);
    auto lt = prev(gt);
    ui left = gt == poles.begin() ? 0 : lt->first;
    if (gt == poles.end() || left == cur) {
      cout << prev(dists.end())->first << ' ';
      continue;
    }
    ui right = gt->first;
    gt->second->second.erase(right);
    if (gt->second->second.empty()) {
      dists.erase(gt->second);
    }
    insert(right, right - cur);
    insert(cur, cur - left);
    cout << prev(dists.end())->first << ' ';
  }
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}
