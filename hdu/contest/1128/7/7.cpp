/*
 * 7.cpp 2024-08-03
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

#include <set>
#include <stack>
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
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int M = 1e5 + 1e4;
const int N = M;

struct Edge {
	i32 to, next;
} e[ M << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

std::vector<i32> list;
bool vis[N], in[N];
void dfs( ci32 cur, ci32 la ) {
	list.push_back(cur);
	vis[cur] = true; in[cur] = true;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 to = e[i].to;
		if( to == la || vis[to] ) 
			continue;
		dfs( to, cur );
	}
}


int main() {
#ifdef woshiluo
	freopen( "7.in", "r", stdin );
	freopen( "7.out", "w", stdout );
#endif


	i32 T = read<i32>();
	while( T -- ) {
		std::set<std::pair<i32, i32>> set;
		ci32 n = read<i32>();
		ci32 m = read<i32>();
		
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 5 ) );
		memset( vis, 0, sizeof(vis[0]) * ( n + 5 ) );
		std::vector< std::vector<i32> > mp( n + 1 );
		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			mp[u].push_back(v);
			mp[v].push_back(u);
		}

		for( int i = 1; i <= m; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();
			add_edge( u, v );
			add_edge( v, u );
			set.insert( std::make_pair( u, v ) );
			set.insert( std::make_pair( v, u ) );
		}

		int res = 0;
		for( int o = 1; o <= n; o ++ ) {
			if( !vis[o] ) {
				dfs(o, 0);
				bool flag = true;
				for( auto &cur: list ) {
					for( auto &to: mp[cur] ) {
						if( !in[to] ) 
							continue;
						if( set.count( std::make_pair( cur, to ) ) ) 
							continue;
						flag = false;
					}
				}
				for( auto &cur: list ) {
					in[cur] = false;
				}
				list.resize(0);
				if( flag )
					res += 1;
				else
					res += 2;
			}
		}
		printf( "%d\n", res );
	}
}
