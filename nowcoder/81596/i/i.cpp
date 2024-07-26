/*
 * i.cpp 2024-07-16
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <stack>
#include <tuple>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1024;
const int K = 4;

char mp[N][N];

enum Direction { LEFT, RIGHT, TOP, BOTTOM };

using Node = std::tuple<i32, i32, Direction>;

bool vis[N][N][4];
Node nxt[N][N][4], pre[N][N][4];
// 0 from top
// 1 from bottom
// 2 from left
// 3 from rig


i32 n, m;

Direction go( ci32 x, ci32 y, Direction  l ) {// {{{
	if( mp[x][y] == '/' ) {
		if( l == TOP ) 
			return RIGHT;
		if( l == BOTTOM ) 
			return LEFT;
		if( l == LEFT ) 
			return BOTTOM;
		if( l == RIGHT ) 
			return TOP;
	}
	if( mp[x][y] == '\\' ) {
		if( l == TOP ) 
			return LEFT;
		if( l == BOTTOM ) 
			return RIGHT;
		if( l == LEFT ) 
			return TOP;
		if( l == RIGHT ) 
			return BOTTOM;
	}
	if( mp[x][y] == '-' ) {
		if( l == TOP ) 
			return BOTTOM;
		if( l == BOTTOM ) 
			return TOP;
		if( l == LEFT ) 
			return LEFT;
		if( l == RIGHT ) 
			return RIGHT;
	}
	if( mp[x][y] == '|' ) {
		if( l == TOP ) 
			return TOP;
		if( l == BOTTOM ) 
			return BOTTOM;
		if( l == LEFT ) 
			return RIGHT;
		if( l == RIGHT ) 
			return LEFT;
	}
	// Should never reach here!
	return LEFT;
}// }}}

int tidx;
int dfn[N][N][4], low[N][N][4];

int res[N][N][4];

std::stack<Node> st;

bool vis2[N][N];
int tot = 0;
std::vector<std::pair<i32,i32>> list;

void erase() {
	for( auto &[x, y]: list )
		vis2[x][y] = false;
	tot = 0;
	list.resize(0);
}

void dfs( ci32 x, ci32 y, Direction l ) {
	tidx ++;

	dfn[x][y][l] = low[x][y][l] = tidx;
	vis[x][y][l] = true;

	st.push( std::make_tuple( x, y, l ) );
	Direction nd = go( x, y, l );
	ci32 nx = x + ( ( nd == TOP )? 1: ( ( nd == BOTTOM )? -1: 0 ) );
	ci32 ny = y + ( ( nd == LEFT )? 1: ( ( nd == RIGHT )? -1: 0 ) );

	if( nx > 0 && ny > 0 && nx <= n && ny <= m ) {
		if( !dfn[nx][ny][nd] ) {
			dfs( nx, ny, nd );
			chk_Min( low[x][y][l], low[nx][ny][nd] );
		}
		else if( vis[nx][ny][nd] ) {
			chk_Min( low[x][y][l], dfn[nx][ny][nd] );
		}
	}
	if( dfn[x][y][l] == low[x][y][l] ) {
		std::vector<Node> nodes;
		Node cur = std::make_tuple( x, y, l );
		while( st.top() != cur ) {
			nodes.push_back( st.top() );
			st.pop();
		}
		nodes.push_back(st.top()); st.pop();
		for( auto &[cx, cy, cd]: nodes ) 
			vis[cx][cy][cd] = false;

		ci32 size = nodes.size();
		if( size == 1 ) 
			return ;
		for( auto &[cx, cy, cd]: nodes ) {
			if( go( cx, cy, cd ) != cd ) {
				if( !vis2[cx][cy] ) {
					vis2[cx][cy] = true;
					tot ++;
					list.push_back(std::make_pair( cx, cy ));
				}
			}
		}
		for( auto &[cx, cy, cd]: nodes ) 
			res[cx][cy][cd] = tot;
		erase();
	}
}


void dfs2( ci32 x, ci32 y, const Direction l ) {
	if( res[x][y][l] != 0 ) 
		return ;
	Direction nd = go( x, y, l );
	ci32 nx = x + ( ( nd == TOP )? 1: ( ( nd == BOTTOM )? -1: 0 ) );
	ci32 ny = y + ( ( nd == LEFT )? 1: ( ( nd == RIGHT )? -1: 0 ) );

	if( nx > 0 && ny > 0 && nx <= n && ny <= m ) 
		dfs2( nx, ny, nd );
	if( !vis2[x][y] ) {
		if( nd != l ) {
			tot ++;
			list.push_back( std::make_pair( x, y ) );
			vis2[x][y] = true;
		}
	}
	res[x][y][l] = tot;
}


int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif

	n = read<i32>();
	m = read<i32>();

	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", mp[i] + 1 );
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			for( int k = 0; k < K; k ++ ) {
				if( !dfn[i][j][k] ) 
					dfs( i, j, (Direction)k );
			}
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		dfs2( i, 1, LEFT );
		erase();
		dfs2( i, m, RIGHT );
		erase();
	}
	for( int j = 1; j <= m; j ++ ) {
		dfs2( 1, j, TOP );
		erase();
		dfs2( n, j, BOTTOM );
		erase();
	}


	i32 q = read<i32>();
	while( q -- ) {
		ci32 x = read<i32>();
		ci32 y = read<i32>();
		static char buf[16];
		scanf( "%s", buf );
		if( buf[0] == 'a' ) {
			ci32 nx = x - 1;
			ci32 ny = y;
			if( nx > 0 && ny > 0 && nx <= n && ny <= m ) 
				printf( "%d\n", res[nx][ny][BOTTOM] );
			else
				printf( "0\n" );
		}
		else if( buf[0] == 'b' ) {
			ci32 nx = x + 1;
			ci32 ny = y;
			if( nx > 0 && ny > 0 && nx <= n && ny <= m ) 
				printf( "%d\n", res[nx][ny][TOP] );
			else
				printf( "0\n" );
		}
		else if( buf[0] == 'l' ) {
			ci32 nx = x;
			ci32 ny = y - 1;
			if( nx > 0 && ny > 0 && nx <= n && ny <= m ) 
				printf( "%d\n", res[nx][ny][RIGHT] );
			else
				printf( "0\n" );
		}
		else if( buf[0] == 'r' ) {
			ci32 nx = x;
			ci32 ny = y + 1;
			if( nx > 0 && ny > 0 && nx <= n && ny <= m ) 
				printf( "%d\n", res[nx][ny][LEFT] );
			else
				printf( "0\n" );
		}
	}
}
