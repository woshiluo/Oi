#include <bits/stdc++.h>

using namespace std;

int main(){
	int a[4];
	int b;
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> b;
	sort(a, a + 4);
	bool ok = false;
	ok |= is_sorted(a, a + 4);
	a[0] += b;
	ok |= is_sorted(a, a + 4);
	
	cout << int(ok) << "\n";			

}
