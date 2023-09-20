#include <bits/stdc++.h>

using namespace std;


int main() {

	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
	
	// for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
	// for (int i = 0; i < n; i++) cout << b[i] << " \n"[i + 1 == n];
	auto A = a;

	vector<int> t;
	for (int i = 0; i < n; i++) {
		int p = -1;
		for (int j = 0; j < n; j++) {
			if (b[i] == a[j]) {
				p = j;
				break;
			}
		}
		for (int j = p - 1; j >= i; j--) {
			swap(a[j], a[j + 1]);
			t.push_back(j);
		}
		// cout << " i : "  << i << "\n";
		// for (int j = 0; j < n; j++) cout << a[j] << " \n"[j + 1 == n];
	}

	bool ok = true;
	for (int i : t) {
		if (abs(A[i] - A[i + 1]) < 2) {
			ok = false;
			break;
		}
		swap(A[i], A[i + 1]);
	}

	if (ok) {
		cout << t.size() << "\n";
		for (int i : t) {
			cout << i + 1 << " ";
		}
		cout << "\n";
	} else {
		cout << -1 << "\n";
	}
}