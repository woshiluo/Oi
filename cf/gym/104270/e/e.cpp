#include <bits/stdc++.h>

using namespace std;

void solve() {
	long long n;
	long long m;
	cin >> n >> m;
	vector<long long> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	auto check = [&](long long x) {
		vector<long long> ned(n + 2, 0LL);
		for (int i = 0; i < n; i++) {
			ned[i] = (x + a[i] - 1) / a[i];
		}
		long long need = 0;
		for (int i = 0; i < n; i++) {
			if (i + 1 == n && ned[i] <= 0) {
				break;
			}
			ned[i] -= 1LL, need++;
			if (ned[i] > 0) {
				need += ned[i] * 2LL;
				ned[i + 1] -= ned[i];
				ned[i] = 0LL;
			}
		}
		return need <= m;
	};
	long long l = 0, r = 1e12 + 1;
	while (r - l > 1) {
		long long mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}	
	}
	cout << l << "\n";
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
