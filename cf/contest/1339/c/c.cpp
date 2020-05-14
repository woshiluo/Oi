// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/12 22:46:22 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

inline int Max( int a, int b ) { return a > b? a: b; }
inline void chk_Max( int &a, int b ) { if( b > a ) a = b; }

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

int T, n, ans;

inline int max_bit( int cur ) {
	int cnt = 0;
	while( cur ) {
		cur /= 2;
		cnt ++;
	}
	return cnt;
}

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int max = -INF; ans = 0;
		for( int i = 1, tmp; i <= n; i ++ ) {
			scanf( "%d", &tmp );
			if( tmp >= max ) 
				max = tmp;
			else 
				chk_Max( ans, Max( 0, max_bit( max - tmp ) ) );
		}
		printf( "%d\n", ans );
	}
}
