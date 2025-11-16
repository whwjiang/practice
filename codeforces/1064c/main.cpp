#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
  int n;
  cin >> n;
  vector<int> nums(n);
  int mn = 0;
  for (int i = 0; i < n; ++i) {
    cin >> nums[i];
    if (nums[i] < nums[mn]) {
      mn = i;
    }
  }
  rotate(nums.begin(), nums.begin() + mn, nums.end());
  vector<int> ngi(n, n);
  vector<int> pgi(n, -1);
  deque<int> s;
  for (int i = 0; i < n; ++i) {
    while (!s.empty() && nums[s.back()] <= nums[i]) {
      ngi[s.back()] = i;
      s.pop_back();
    }
    s.push_back(i);
  }

  for (int i = n - 1; i >= 0; --i) {
    while (!s.empty() && nums[s.back()] <= nums[i]) {
      pgi[s.back()] = i;
      s.pop_back();
    }
    s.push_back(i);
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    cout << ngi[i] << ", " << pgi[i] << endl;
    int next = ngi[i] == n ? INT_MAX : nums[ngi[i]];
    int prev = pgi[i] == -1 ? INT_MAX : nums[pgi[i]];
    if (next != INT_MAX || prev != INT_MAX) {
      ans += min(next, prev);
    }
  }
  cout << ans << endl;
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
