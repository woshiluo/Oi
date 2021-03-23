// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 11:50:23 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

long long aabs( long long cur ) { return cur < 0? -cur: cur; }
long long gcd( long long a, long long b ) { 
	return b? gcd( b, a % b ): a; 
}

const int N = 2e5 + 1e4;

long long x[N];

bool work() {
	int n;
	long long k, d = 0;
	scanf( "%d%lld", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &x[i] );
		if( i == 2 ) {
			d = x[i] - x[ i - 1 ];
		}
		else if( i >= 2 ) {
			d = gcd( d, x[i] - x[ i - 1 ] );
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( ( k - x[i] ) % d == 0 ) 
			return true;
	}
	return false;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}
