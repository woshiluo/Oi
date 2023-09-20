#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

inline int Min( int a, int b ) { return a < b? a: b; }
inline void chk_Min( int &a, int b ) { a = Min( a, b ); }
inline int Max( int a, int b ) { return a > b? a: b; }
inline void chk_Max( int &a, int b ) { a = Max( a, b ); }
inline int aabs( int a ) { return a < 0? -a: a; }

const int N = 310;
const int INF = 0x3f3f3f3f;

int n, m;
int f[N][N];
char a[N], b[N];
std::vector<int> pool[N];

int dfs( int cur, int pos ) {
	if( f[cur][pos] != -1 ) 
		return f[cur][pos];
	else
		f[cur][pos] = INF;
	if( pos == m ) {
		f[cur][pos] = 0;
		return 0;
	}

	if( cur + 1 <= n && pos + 1 <= m && a[ cur + 1 ] == b[ pos + 1 ] ) 
		chk_Min( f[cur][pos], dfs( cur + 1, pos + 1 ) + 1 );
	if( cur - 1 >= 1 && pos + 1 <= m && a[ cur - 1 ] == b[ pos + 1 ] ) 
		chk_Min( f[cur][pos], dfs( cur - 1, pos + 1 ) + 1 );

	for( auto x: pool[ a[cur] ] )  {
		chk_Min( f[cur][pos], dfs( x, pos ) + aabs( x - cur ) );
	}

	return f[cur][pos];
}

int main() {
	freopen( "word.in", "r", stdin );
	freopen( "word.out", "w", stdout );

	memset( f, -1, sizeof(f) );
	scanf( "%d%d", &n, &m );
	scanf( "%s", a + 1 );
	scanf( "%s", b + 1 );
	for( int i = 1; i <= n; i ++ ) 
		pool[ a[i] ].push_back(i);

	int ans = INF;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] == b[1] ) {
			dfs( i, 1 );
			chk_Min( ans, f[i][1] );
		} 
	}

	printf( "%d\n", ans == INF? -1: ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
