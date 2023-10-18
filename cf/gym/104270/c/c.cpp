#include<bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		string s;
		string t;
		cin >> s >> t;
		vector<int> w(n);
		for (int i = 0; i < n; i++) {
			w[i] = s[i] ^ t[i];
		}
		vector<int> seg;
		for (int i = 0, j = 0; i < n; i = j) {
			j = i;
			while (j < n && w[i] == w[j]) {
				j += 1;
			}
			if (w[i] == 1) {
				seg.push_back(j - i);
			}
		} if (seg.size() == 0) {
			cout << 1ll * n * (n + 1) / 2 << "\n";
		} else if (seg.size() == 1) {
		// n - l + 1
		// [l, t] [r+1,t], t<=n -> n-r
		// [t, r] [t,l-1], t>=1 -> l-1
		// [l, t] [t+1,r], r-l
			int res = 2 * (n - 1);
			cout << res << "\n";
		} else if (seg.size() == 2) {
			cout << 6 << "\n";
		} else cout << 0 << "\n";
	}
}
