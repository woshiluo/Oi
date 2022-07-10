/*
 * luogu.4294.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 11;
const int INF = 0x3f3f3f3f;

int mark[ N * N ];
int a[N][N];
int f[ N * N ][ 1 << N ];
std::pair<int, int> la[ N * N ][ 1 << N ];

int dx[] = { +1, -1, 0, 0 };
int dy[] = { 0, 0, +1, -1 };

int full_pow( cint cur ) { return 1 << cur; }
bool chk_pos( cint cur, cint pos ) { return cur & full_pow(pos); }

void dfs( cint cur, cint st ) {
	if( mark[cur] == 0 ) 
		mark[cur] = 1;

	cint nxt = la[cur][st].first;
	cint nst = la[cur][st].second;

	if( nst == 0 ) 
		return ;

	if( nxt == 0 ) {
		dfs( cur, nst );
		dfs( cur, st ^ nst );
	}
	else
		dfs( nxt, nst );
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4294.in", "r", stdin );
	freopen( "luogu.4294.out", "w", stdout );
#endif
	memset( f, INF, sizeof(f) );

	cint n = read<int>();
	cint m = read<int>();

	std::vector<int> list;
	auto hash = [&m] ( cint i, cint j ) { return ( i - 1 ) * m + j; };
	auto get_i = [&m] ( cint cur ) { return cur / m - ( cur % m == 0 ) + 1; };
	auto get_j = [&m] ( cint cur ) { return ( cur % m == 0 )? m: ( cur % m ); };

	for( int i = 1; i <= n; i ++ ) {/*{{{*/
		for( int j = 1; j <= m; j ++ ) {
			a[i][j] = read<int>();
			f[ hash( i, j ) ][0] = 0;
			if( a[i][j] == 0 ) {
				mark[ hash( i, j ) ] = 2;
				f[ hash( i, j ) ][ full_pow( list.size() ) ] = 0;
				list.push_back( hash( i, j ) );
			}
		}
	}/*}}}*/


	cint k = list.size();
	for( int st = 0; st < full_pow(k); st ++ ) {/*{{{*/
		std::priority_queue<std::pair<int, int>> q;
		for( int u = 1; u <= n * m; u ++ ) {
			for( int s1 = st; s1; s1 = ( s1 - 1 ) & st ) {
				cint s2 = st ^ s1;
				if( s2 == 0 ) 
					continue;
				if( f[u][s1] + f[u][s2] - a[ get_i(u) ][ get_j(u) ] < f[u][st] ) {
					chk_Min( f[u][st], f[u][s1] + f[u][s2] - a[ get_i(u) ][ get_j(u) ] );
					la[u][st] = std::make_pair( 0, Max( s1, s2 ) );
				}
			}
			if( f[u][st] != INF ) 
				q.push( std::make_pair( -f[u][st], u ) );
		}

		auto dij = [&] () {
			static bool vis[ N * N ];
			memset( vis, false, sizeof(vis) );
			while( !q.empty() ) {
				cint cur = q.top().second; q.pop();
				if( vis[cur] ) 
					continue;
				vis[cur] = true;
				for( int i = 0; i < 4; i ++ ) {
					cint nx = get_i(cur) + dx[i];
					cint ny = get_j(cur) + dy[i];
					
					if( nx < 1 || ny < 1 || nx > n || ny > m ) 
						continue;

					cint nxt = hash( nx, ny );
					if( f[cur][st] + a[nx][ny] < f[nxt][st] ) {
						f[nxt][st] = f[cur][st] + a[nx][ny];
						la[nxt][st] = std::make_pair( cur, st );
						q.push( std::make_pair( -f[nxt][st], nxt ) );
					}
				}
			}
		};

		dij();
	}/*}}}*/

	int min = 0;
	cint full = full_pow(k) - 1;
	for( int i = 1; i <= n * m; i ++ ) {
		if( f[i][full] < f[min][full] )
			min = i;
	}

	printf( "%d\n", f[min][full] );

	dfs( min, full );

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			cint h = hash( i, j );
			if( mark[h] == 0 ) 
				printf( "_" );
			if( mark[h] == 1 ) 
				printf( "o" );
			if( mark[h] == 2 ) 
				printf( "x" );
		}
		printf( "\n" );
	}
}
