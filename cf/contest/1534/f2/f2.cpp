/*
 * f2.cpp
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

int n, m;
int a[N];
std::vector<int> spei;

namespace tarjan {
}

int main() {
	scanf( "%d%d", &n, &m );
	std::vector<int> pos[N];
	{/*{{{*/
		int id_cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%s", str + 1 );
			for( int j = 1; j <= m; j ++ ) {
				id[i][j] = id_cnt ++;
				mp[i][j] = ( str[i][j] == '#' );
				pos[i].push_back(i);
			}
		}
		for( int i = 1; i <= m; i ++ ) {
			std::sort( pos[i].begin(), pos[i].end() );
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( !mp[i][j] ) 
					continue;
				// try i, j + 1 
				if( j + 1 <= m && mp[i][ j + 1 ] ) 
					add_edge( id[i][j], id[i][ j + 1 ] );
				// try i, j - 1 
				if( j - 1 >= 1 && mp[i][ j - 1 ] ) 
					add_edge( id[i][j], id[i][ j - 1 ] );
				// try i - 1, first_leq(j)
				{
					int pos = std::upper_bound( pos[ i - 1 ].begin(), pos[ i - 1 ].end(), j ) - pos[ i - 1 ].begin() - 1;
					if( pos != - 1 ) {
						add_edge( id[i][j], id[ i - 1 ][pos] );
					}
				}
				// try i + 1, first_leq(j)
				{
					int pos = std::upper_bound( pos[ i + 1 ].begin(), pos[ i + 1 ].end(), j ) - pos[ i + 1 ].begin() - 1;
					if( pos != - 1 ) {
						add_edge( id[i][j], id[ i + 1 ][pos] );
					}
				}
			}
		}
	}/*}}}*/
	tarjan::tarjan();
	{
		std::vector<int> tsp;
		bool vis[N]; memset( vis, 0, sizeof(vis) );
		for( int i = 1; i <= m; i ++ ) {
			a[i] = read<int>();
			tsp[i].push_back( id[i][ pos[i][ a[i] - 1 ] ] );
		}
		for( auto &x: tsp ) {
			if( !vis[x] ) {
				dfs(x);
				vis[x] = false;
			}
		}
	}
}
