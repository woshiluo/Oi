// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/28 00:30:18 
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

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;

int a[N], b[N];
int p[N];

inline int calc( int left, int rig, int val ) {
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( p[mid] <= val ) 
			left = mid + 1;
		else 
			rig = mid - 1;
	}
	return left - 1;
}

inline void no_ans() {
	printf( "-1\n" );
	exit(0);
}

inline int query( int left, int rig ) {
	if( rig < left ) 
		return 0;
	int len = rig - left + 1;
	p[0] = -INF;
	for( int i = 1; i <= len; i ++ ) {
		p[i] = INF;
	}
	int res = 0;
	for( int i = left; i <= rig; i ++ ) {
		if( a[ left - 1 ] <= a[i] && a[i] <= a[ rig + 1 ] ) {
			int pos = calc( 0, len, a[i] ) + 1;
			chk_Max( res, pos );
			if( a[i] < p[pos] )
				p[pos] = a[i];
		}
	}
	return ( rig - left + 1 ) - res;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, k, ans = 0;
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		a[i] -= i;
	}
	a[0] = -INF, a[ n + 1 ] = INF;
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d", &b[i] );
	}
	for( int i = 1; i <= k; i ++ ) {
		if( a[ b[i - 1] ] > a[ b[i] ] )
			no_ans();
		ans += query( b[ i - 1 ] + 1, b[i] - 1 );
	}
	ans += query( b[k] + 1, n );
	printf( "%d\n", ans );
}
