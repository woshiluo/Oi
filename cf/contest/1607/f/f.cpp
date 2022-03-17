/*
 * f.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <stack>
#include <vector>
#include <algorithm>

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

const int N = 2100;

struct Node { int x, y; };

int n, m, idx;
std::stack<Node> st;
int dfn[N][N], low[N][N], mp[N][N], dis[N][N];
bool vis[N][N];
int cmap[512];

// 0 L 
// 1 R
// 2 U
// 3 D
int dx[4] = { 0, 0, -1, +1 };
int dy[4] = { -1, +1, 0, 0 };
void tarjan( int x, int y ) {
	auto check = []( int cx, int cy ) {
		if( cx <= 0 || cy <= 0 || cx > n || cy > m ) 
			return false;
		return true;
	};
	idx ++; vis[x][y] = true; dfn[x][y] = idx; low[x][y] = idx;
	st.push( (Node) { x, y } );
	int p = mp[x][y];
	int nx = x + dx[p], ny = y + dy[p];
	if( check( nx, ny ) ) {
		if( !dfn[nx][ny] ) {
			tarjan( nx, ny );
			chk_Min( low[x][y], low[nx][ny] );
		}
		else if( vis[nx][ny] )
			chk_Min( low[x][y], dfn[nx][ny] );
	}
	else {
		vis[x][y] = false; st.pop(); dis[x][y] = 1;
		return ;
	}

	if( dfn[x][y] == low[x][y] ) {
		std::vector<Node> res;
		auto check_top = [x,y](){ 
			if( st.empty() ) 
				return false;
			Node top = st.top();
			return low[top.x][top.y] == dfn[x][y];
		};
		while( check_top() ) {
			Node top = st.top(); st.pop();
			vis[ top.x ][ top.y ] = false;
			res.push_back(top);
		}

		if( res.size() == 1 ) 
			dis[x][y] = dis[nx][ny] + 1;
		else
			for( auto node: res ) 
				dis[node.x][node.y] = res.size();
	}
}

void calc() {
	idx = 0;
	while( !st.empty() ) st.pop();
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		static char str[N];
		scanf( "%s", str + 1 );
		for( int j = 1; j <= m; j ++ ) {
			vis[i][j] = false;
			low[i][j] = dfn[i][j] = dis[i][j] = 0;
			mp[i][j] = cmap[ str[j] ];;
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			if( !dfn[i][j] ) 
				tarjan( i, j );
		}
	}
	int gx, gy;
	gx = gy = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			if( dis[i][j] > dis[gx][gy] ) 
				gx = i, gy = j;
		}
	}
	printf( "%d %d %d\n", gx, gy, dis[gx][gy] );
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int T = read<int>();
	cmap['L'] = 0; cmap['R'] = 1;
	cmap['U'] = 2; cmap['D'] = 3;
	while( T -- ) {
		calc();
	}
}
