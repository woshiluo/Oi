// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/02 23:10:14 
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

const int N = 2e5 + 1e4;

struct node {
	int id, val;
};

bool cmp( node _a, node _b ) {
	return _a.val < _b.val;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		int b[N];
		long long sum[N];
		node a[N];
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i].val );
			a[i].id = i;
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
		}

		std::sort( a + 1, a + n + 1, cmp );
		for( int i = 1; i <= n; i ++ ) {
			sum[i] = sum[ i - 1 ] + b[ a[i].id ];
		}
		long long ans = ( 1LL << 60LL );
		for( int i = 0; i <= n; i ++ ) { 
			chk_Min( ans, Max( (long long)a[i].val, sum[n] - sum[i] ) );
		}

		printf( "%lld\n", ans );
	}
}
