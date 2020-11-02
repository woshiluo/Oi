#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 510;
const int M = 2e4 + 1e3;
const int INF = 0x3f3f3f3f;

inline void chk_Min( int &a, int b ) { a = std::min( a, b ); }
inline void chk_Max( int &a, int b ) { a = std::max( a, b ); }

int n, m;
int p[M], f[M];

bool cmp( int _a, int _b ) { return _a > _b; }

int main() {
#ifdef woshiluo
	freopen( "bread.in", "r", stdin );
	freopen( "bread.out", "w", stdout );
#endif
	scanf( "%d%d", &m, &n );
	memset( f, INF, sizeof(f) );
	f[0] = 0;
	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d", &p[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		int c, v;
		scanf( "%d%d", &c, &v );
		for( int j = (int)(2e4); j >= c; j -- ) {
			chk_Min( f[j], f[ j - c ] + v );
		}
	}
	for( int i = (int)(2e4) - 1; i >= 1; i -- ) {
		chk_Min( f[i], f[ i + 1 ] );
	}
	std::sort( p + 1, p + m + 1, cmp );
	int ans = 0, sum = 0;
	for( int i = 1; i <= m; i ++ ) {
		sum += p[i];
		if( f[i] != INF ) {
			chk_Max( ans, sum - f[i] );
		}
	}
	printf( "%d\n", ans );

	return 0;
}
