/*
 * l.cpp 2024-09-13
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
#include <cinttypes>

#include <set>
#include <queue>
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

const int N = 1e5 + 1e4;
const int M = 1e5 + 1e4;

const int INF = 0x3f3f3f3f;

struct Edge {
	i32 to, next, val;
} e[ M << 1 ];
i32 ehead[N], ecnt;
void add_edge( ci32 from, ci32 to, ci32 val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

struct Gate { int id, p, l, r; };

int a[N];

std::vector<i32> dij( ci32 st, ci32 n ) {
	std::vector<i32> dis( n + 1, INF );
	std::vector<i32> vis( n + 1, false );

	std::priority_queue<std::pair<i32, i32>> q;
	dis[st] = 0;
	q.push( std::make_pair( -dis[st], st ) );
	while( !q.empty() ) {
		const auto [ _, x ] = q.top(); q.pop();
		if( vis[x] ) 
			continue;
		vis[x] = true;
		for( int i = ehead[x]; i; i = e[i].next ) {
			if( e[i].val + dis[x] < dis[ e[i].to ] ) {
				dis[ e[i].to ] = dis[x] + e[i].val;
				if( !vis[ e[i].to ] ) {
					q.push( std::make_pair( -dis[ e[i].to ], e[i].to ) );
				}
			}
		}
	}

	return dis;
}

int main() {
#ifdef woshiluo
	freopen( "l.in", "r", stdin );
	freopen( "l.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 m = read<i32>();
	ci32 k = read<i32>();
	ci32 T = read<i32>();

	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<i32>();

	std::vector<Gate> gates;
	for( int i = 0; i < k; i ++ ) {
		ci32 p = read<i32>();
		ci32 l = read<i32>();
		ci32 r = read<i32>();

		gates.push_back( { i, p, l, r } );
	}

	for( int i = 1; i <= m; i ++ ) {
		ci32 u = read<i32>();
		ci32 v = read<i32>();
		ci32 w = read<i32>();

		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	std::vector<std::vector<i32>> in( T + 1 ), out( T + 1 );
	std::vector<std::vector<i32>> dis;
	for( const auto &[id, p, l, r]: gates ) {
		dis.emplace_back(dij(p, n));
		in[l].push_back(id);
		out[r].push_back(id);
	}

	bool flag = true;
	i64 res = 0;
	std::set<i32> set;
	std::vector<i32> cur_dis( n + 1 );
	for( int o = 1; o <= T; o ++ ) {
		for( auto &p: in[o] ) {
			flag = true;
			set.insert( gates[p].id );
		}

		if( flag ) {
			flag = false;
			cur_dis.resize(0);
			cur_dis.resize( n + 1, INF );
			for( auto &p: set ) {
				for( int i = 1; i <= n; i ++ ) 
					chk_Min( cur_dis[i], dis[p][i] );
			}
			res = 0;
			for( int i = 1; i <= n; i ++ ) {
				res += 1LL * cur_dis[i] * a[i];
			}
		}

		if( set.empty() ) 
			printf( "-1\n" );
		else
			printf( "%" PRId64 "\n", res );

		for( auto &p: out[o] ) {
			flag = true;
			set.erase( gates[p].id );
		}
	}

}
