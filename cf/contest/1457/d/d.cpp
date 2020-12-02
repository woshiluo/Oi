// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/29 16:10:07 
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

int n;
int sum[N];

inline int query( int left, int rig ) {
	return sum[rig] ^ sum[ left - 1];
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &n );
	if( n > 60 ) {
		printf( "1\n" );
		return 0;
	}
	
	for( int i = 1; i <= n; i ++ ) {
		int tmp;
		scanf( "%d", &tmp );
		sum[i] = sum[ i - 1 ] ^ tmp;
	}

	int ans = n;
	for( int i = 1; i < n; i ++) {
		for( int j = 1; j <= i; j ++ ) {
			for( int k = i + 1; k <= n; k ++ ) {
				if( query( j, i ) > query( i + 1, k ) )
					chk_Min( ans, ( i - j ) + ( k - ( i + 1 ) )  );
			}
		}
	}
	printf( "%d\n", ans == n? -1: ans );
}
