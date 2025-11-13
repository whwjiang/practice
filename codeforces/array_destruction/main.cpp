#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<pair<int, int>> soln;

bool feasible(const vector<int> &nums, int x, int n) {
  multiset<int> s(nums.begin(), nums.end());
  while (!s.empty()) {
    auto git = prev(s.end());
    if (git == s.begin()) {
      return false;
    }
    auto mit = s.find(x - *git);
    if (mit == s.end() || mit == git) {
      return false;
    }
    soln.push_back({*mit, *git});
    x = max(*git, *mit);
    s.erase(git);
    s.erase(mit);
  }
  return soln.size() == n;
}

void solve() {
  int n;
  cin >> n;
  int m = 2 * n;
  vector<bool> used(m, false);
  vector<int> nums;
  nums.reserve(m);
  int cur;
  for (int i = 0; i < m; ++i) {
    cin >> cur;
    nums.push_back(cur);
  }
  sort(nums.begin(), nums.end());
  for (int i = m - 2; i >= 0; --i) {
    soln.clear();
    if (feasible(nums, nums[i] + nums[m - 1], n)) {
      cout << "YES" << endl;
      cout << nums[i] + nums[m - 1] << endl;
      for (const auto &[v1, v2] : soln) {
        cout << v1 << ' ' << v2 << endl;
      }
      return;
    }
  }
  cout << "NO" << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  if (!(cin >> t))
    return 0;
  while (t--)
    solve();
}
