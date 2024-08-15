/*
 * d1.cpp 2024-08-11
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

const int N = 5e5 + 1e4;

struct Edge {
	i32 to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from]; 
	ehead[from] = ecnt;
}

i32 fa[N], size[N];

std::vector<i32> son[N];

void dfs( ci32 cur ) {
	size[cur] = 1;
	for( auto &to: son[cur] ) {
		dfs(to);
		size[cur] += size[to];
	}
}

int main() {
#ifdef woshiluo
	freopen( "d1.in", "r", stdin );
	freopen( "d1.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 q = read<i32>();
		for( int i = 1; i <= n; i ++ ) 
			son[i].resize(0);
		for( int i = 2; i <= n; i ++ ) {
			ci32 u = read<i32>();
			son[u].push_back(i);
			fa[i] = u;
		}

		dfs(1);

		std::vector<i32> p( n + 1 ), id( n + 1 );
		for( int i = 1; i <= n; i ++ ) {
			p[i] = read<i32>();
			id[ p[i] ] = i;
		}

		i32 cnt = 0;
		std::vector<bool> invalid( n + 1, false );

		auto check_pos = [&] ( ci32 pos ) {
			cnt -= invalid[pos];
			ci32 rid = p[pos];
			bool flag = true;
			if( son[rid].size() != 0 ) {
				if( pos + 1 > n || pos + 1 + size[ son[rid][0] ] > n ) 
					flag = false;
				else {
					{
						ci32 nxt = p[ pos + 1 ];
						if( son[rid][0] != nxt && son[rid][1] != nxt ) {
							flag = false;
						}
					}
					{
						ci32 nxt = p[ pos + 1 + size[ son[rid][0] ] ];
						if( son[rid][0] != nxt && son[rid][1] != nxt ) {
							flag = false;
						}
					}
				}
			}
			invalid[pos] = ( !flag );
			cnt += invalid[pos];
		};
		for( int i = 1; i <= n; i ++ ) 
			check_pos(i);

		for( int _ = 1; _ <= q; _ ++ ) {
			ci32 x = read<i32>();
			ci32 y = read<i32>();

			std::swap( p[x], p[y] );

			id[ p[x] ] = x; id[ p[y] ] = y;

			check_pos(x);
			check_pos(y);

			if( p[x] != 1 )
				check_pos( id[ fa[ p[x] ] ] );
			if( p[y] != 1 )
				check_pos( id[ fa[ p[y] ] ] );

			if( cnt == 0 ) 
				printf( "YES\n" );
			else 
				printf( "NO\n" );
		}
	}
}
