// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/04 14:15:29 
#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1100;

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }
template<class T> 
T aabs( T a ) { return a < 0? -a: a; }

int n, m;
int a[N];

inline int add( int a, int b ) { return ( a + b ) % m; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % m; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	if( n > m ) {/*{{{*/
		printf( "0\n" );
		return 0;
	}/*}}}*/
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	int ans = 1;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			ans = mul( ans, aabs( a[i] - a[j] ) );
		}
	}
	printf( "%d\n", ans );
}
