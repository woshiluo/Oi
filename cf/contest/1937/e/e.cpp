/*
 * e.cpp 2024-03-01
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

#include <map>
#include <queue>
#include <vector>
#include <algorithm>

#ifdef woshiluo
#include <cassert>
#endif

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


const int N = 4e5 + 1e4;
const int NM = 4e5 + 1e4;
const i64 LLF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, next, val; 
} e[NM * 20];
int ehead[NM*3], ecnt;
void add_edge( ci32 from, ci32 to, ci32 val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		ci32 tot_nodes = ( n * m * 2 ) + n;

		ecnt = 0;
		memset( ehead, 0, sizeof(int) * ( tot_nodes + 5 ) );

		std::vector<i32> c(n + 1);
		std::vector<std::vector<i32>> a( n + 1, std::vector<i32> ( m + 1 ) );
		for( int i = 1; i <= n; i ++ ) {
			c[i] = read<i32>();
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				a[i][j] = read<i32>();
			}
		}
		for( int cur_attr = 1; cur_attr <= m; cur_attr ++ ) {/*{{{*/
			ci32 x_base = ( cur_attr - 1 ) * 2 * n + n;
			ci32 y_base = x_base + n;
#ifdef woshiluo
			assert( y_base + n <= tot_nodes );
#endif
			std::vector<i32> list;
			std::map<i32, i32> mp;
			for( int i = 1; i <= n; i ++ ) {
				mp[ a[i][cur_attr] ] ++;
				list.push_back( a[i][cur_attr] );
			}
			list.push_back(0);
			std::sort( list.begin(), list.end() );
			std::vector<i32> rarr( n + 1 );
			int la = 0;
			for( auto &[key, val]: mp ) {
				val += mp[la];
				la = key;
			}
			for( int i = n; i >= 1; i -- ) {
				rarr[i] = mp[ a[i][cur_attr] ];
				mp[ a[i][cur_attr] ] --;
			}
			for( int i = 1; i <= n; i ++ ) {
				add_edge( x_base + i, y_base + i, 0 );
			}
			for( int i = 2; i <= n; i ++ ) {
				add_edge( x_base + i - 1, x_base + i, list[i] - list[ i - 1 ] );
				add_edge( y_base + i, y_base + i - 1, 0 );
			}
			for( int i = 1; i <= n; i ++ ) {
				add_edge( i, x_base + rarr[i], c[i] );
				add_edge( y_base + rarr[i], i, 0 );
			}
		}/*}}}*/

		{/*{{{*/
			struct Node {
				i32 cur;
				i64 dis;
				bool operator< ( const Node &_b ) const { return dis > _b.dis; }
			};
			std::vector<i64> dis( tot_nodes + 1, LLF );
			std::vector<bool> vis( tot_nodes + 1, false );
			dis[n] = 0;
			std::priority_queue<Node> q;
			q.push( (Node){ n, 0 } );
			while( !q.empty() ) {
				const auto [ cur, _ ] = q.top();
				q.pop();
				if( vis[cur] ) 
					continue;
				vis[cur] = true;
				for( int i = ehead[cur]; i; i = e[i].next ) {
					ci32 to = e[i].to;
					if( dis[to] > dis[cur] + e[i].val ) {
						dis[to] = dis[cur] + e[i].val;
						if( !vis[to] ) {
							q.push( (Node){ to, dis[to] } );
						}
					}
				}
			}
			printf( "%lld\n", dis[1] );
		}/*}}}*/
	}
}
