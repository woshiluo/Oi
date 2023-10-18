#include <bits/stdc++.h>

using namespace std;

void solve() {
	int n, k;
	cin >> n >> k;
	if (n % 2 == 1) {
		cout << "Impossible\n";
		return;
	}
	vector<vector<int>> b;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		int bat = i ^ 1;
		a.push_back(bat);
	}
	b.emplace_back(a);
	
	a.clear();
	auto dfs = [&](auto self, int u) -> void {
		if (u == n) {
			
		}	
		
	};
	if (b.size() < k) {
		cout << "Impossible\n";
		return;
	}
	sort(b.begin(), b.end());
	for (int i = 0; i < k; i++)
		for (int j = 0; j < n; j++)
			cout << b[i][j] + 1 << " \n"[j + 1 == n];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while (t--) {
		solve();
	
	}
}
