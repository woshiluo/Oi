// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/29 15:08:26 
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

inline int dx( int a, int b ) {
	if( b < a ) 
		return 0;
	return 1LL * ( b - a + 1 ) * ( b + a );
}

inline int aabs( int a ) { return a < 0? -a: a; }

inline int mhd( int a, int b, int c, int d ) {
	return aabs( a - c ) + aabs( b - d );
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, m, r, c;
		scanf( "%d%d%d%d", &n, &m, &r, &c );
		long long ans = Max( Max( mhd( 1, 1, r, c ), mhd( 1, m, r ,c ) ),
				Max( mhd( n, 1, r, c ), mhd( n, m, r, c ) ) );
		printf( "%lld\n", ans );
	}
}
