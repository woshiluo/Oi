// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/29 15:43:21 
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

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

int T;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		int n, p, k, x, y, ans = INF;
		static int nxt[N], res[N], a[N];
		scanf( "%d%d%d", &n, &p, &k );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%1d", &a[i] );
		}
		scanf( "%d%d", &x, &y );
		for( int i = 1; i <= n; i ++ ) {
//			if( i + k > n ) 
//				la[ n + 1 ] = i;
//			else
//				la[ i + k ] = i;
			if( i + k > n ) 
				nxt[i] = n + 1;
			else 
				nxt[i] = i + k;
		}
		res[ n + 1 ] = 0;
		for( int i = n; i >= p; i -- ) {
			res[i] = res[ nxt[i] ] + ( a[i] == 0 ) * x;
			chk_Min( ans, res[i] + ( i - p ) * y );
		}
		printf( "%d\n", ans );
	}
}
