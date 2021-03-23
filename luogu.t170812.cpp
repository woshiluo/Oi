#include <cstdio>
#include <cstring>

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;

inline void chk_Min( int &a, int b ) { if( a > b ) a = b; }
inline void chk_Max( int &a, int b ) { if( a < b ) a = b; }

int n, m, k, res = INF;
char a[N], b[N];
int f[2][N];

int main() {
#ifdef woshiluo
	freopen( "luogu.t170812.in", "r", stdin );
	freopen( "luogu.t170812.out", "w", stdout );
#endif
	memset( f, INF, sizeof(f) );

	scanf( "%d%d%d", &n, &m, &k );
	scanf( "%s%s", a + 1, b + 1 );

	int cur = 1, la = 0;
	f[la][0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( int offset = -k; offset <= k; offset ++ ) {
			int j = i + offset;
			if( j <= 0 || j > m )
				continue;
			f[cur][j] = INF;

			if( a[i] == b[j] ) 
				chk_Min( f[cur][j], f[la][ j - 1 ] );
			chk_Min( f[cur][j], f[la][ j - 1 ] + 2 );
			chk_Min( f[cur][j], f[la][j] + 1 );
			chk_Min( f[cur][j], f[cur][ j - 1 ] + 1 );
		}
		f[la][0] = INF;
		cur ^= 1, la ^= 1;
	}
	printf( "%d\n", f[la][m] > k? -1: f[la][m] );
}
