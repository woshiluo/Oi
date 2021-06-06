#include <cstdio>

#include <algorithm>

const int N = 1e5 + 1e4;
const int mod = 1e9 + 7;

int a[N];

int main() {
	int n;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	std::sort( a + 1, a + n + 1 );
	int res = 1;
	for( int i = 1; i < n; i ++ ) {
		res = ( 1LL * res * ( a[ i + 1 ] - a[i] + 1 ) ) % mod;
	}
	res = ( 1LL * res * ( a[1] + 1 ) ) % mod;
	printf( "%d\n", res );
}
