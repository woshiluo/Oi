/*
 * j.cpp 2024-09-26
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

const i32 N = 1e5 + 1e4;

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

int main() {
#ifdef woshiluo
	freopen( "j.in", "r", stdin );
	freopen( "j.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 x = read<i32>();
	for( int i = 0; i < n; i ++ ) {
		ci32 nxt = read<i32>();
		add_edge( i, ( i + nxt ) % n );
		if( i == 0 ) 
			add_edge( n, nxt );
	}
	for( int i = 0; i < n; i ++ ) 
		add_edge( i, ( i + 1 ) % n );

	std::queue<i32> q;
	std::vector<i32> dis( n + 1, 0x3f3f3f3f );
	q.push(n);
	dis[n] = 0;
	while( !q.empty() ) {
		ci32 cur = q.front(); q.pop();
		for( int i = ehead[cur]; i; i = e[i].next ) {
			ci32 to = e[i].to;
			if( dis[cur] + 1 < dis[to] ) {
				dis[to] = dis[cur] + 1;
				q.push(to);
			}
		}
	}
	printf( "%d\n", dis[x] );
}
