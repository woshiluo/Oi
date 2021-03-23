// Woshiluo<woshiluo@woshiluo.site>
// 2LL02LL1/01/2LL8 2LL3:2LL3:14 
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
inline int aabs( int a ) { return a < 0? -a: a; }

const int N = 2e5 + 1e4;

int T;
long long a[N], b[N], c[N];

bool work() { 
	int n;
	long long sum = 0;
	scanf( "%d", &n );
	for( int i = 1; i <= 2LL * n; i ++ ) {
		scanf( "%lld", &a[i] );
//		sum += a[i];
	}
	std::sort( a + 1, a + 2LL * n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( a[ 2LL * i - 1 ] == a[ 2LL * i ] ) {
			b[i] = a[ 2LL * i ];
		}
		else 
			return false;
	}
	for( int i = 1; i < n; i ++ ) {
		if( ( b[ i + 1 ] == b[i] ) || ( b[ i + 1 ] - b[ i ] ) % ( 2LL * i ) != 0 ) {
			return false;
		}
		else {
			c[i] = c[ i - 1 ] + ( b[ i + 1 ] - b[i] ) / ( 2LL * i );
			a[1] -= 2 * c[i];
		}
	}
	if( a[1] <= 0 || a[1] % ( 2 * n ) != 0 )
		return false;
	return true;
}

int main() {
#ifdef woshiluo 
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}
