#include <cmath>
#include <cstdio>

const int N = 1e5 + 1e4;
const int mod = 100003;

inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline int add( int a, int b ) { 
	return ( ( ( a + b ) % mod ) + mod ) % mod; 
}

int a[N], f[N];

int ksm( int a, int p ) {
	int res = 1;
	while( p ) {
		if( p & 1 ) 
			res = mul( res, a );
		a = mul( a, a );
		p >>= 1;
	}
	return res;
}

int frac( int n ) {
	int res = 1;
	for( int i = 2; i <= n; i ++ ) 
		res = mul( res, i );
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "loj.2145.in", "r", stdin );
	freopen( "loj.2145.out", "w", stdout );
#endif
	int n, k;
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	int cnt = 0;
	for( int i = n; i >= 1; i -- )  {
		if( a[i] == 1 ) {
			cnt ++;
			for( int j = 1; j * j <= i; j ++ ) {
				if( i % j == 0 ) {
					a[j] ^= 1; 
					if( i / j != j )
						a[ i / j ] ^= 1;
				}
			}
		}
	}

	for( int i = n; i >= 1; i -- ) {
		f[i] = mul( add( n, mul( add( n, -i ), f[ i + 1 ] ) ),
				ksm( i, mod - 2 ) );
	}

	if( cnt <= k ) {
		printf( "%d\n", mul( cnt, frac(n) ) );
		return 0;
	}

	int ans = k;
	for( int i = k + 1; i <= cnt; i ++ ) 
		ans = add( ans, f[i] );

	printf( "%d\n", mul( ans, frac(n) ) );

}
