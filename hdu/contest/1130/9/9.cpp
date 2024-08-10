/*
 * 9.cpp 2024-08-09
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

struct Edge {
	i32 to, next, val;
} e[N];
int ehead[N], ecnt;
void add_edge( ci32 from, ci32 to, ci32 val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[from];
	ehead[from] = ecnt;
}

const i64 MAX = 1e9;
const i64 MAX_VALID = 1e10;

int base[N];
i64 cnt[N];
i64 f[N];

void dfs( ci32 cur ) {
	f[cur] = 0;
	if( ehead[cur] == 0 ) {
		f[cur] = cnt[cur] * base[cur];
		return ;
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		ci32 val = e[i].val;
		ci32 to = e[i].to;

		cnt[to] = cnt[cur] * val;
		chk_Min( cnt[to], MAX_VALID );
		dfs( to );
		f[cur] += f[to];
	}
}

int main() {
#ifdef woshiluo
	freopen( "9.in", "r", stdin );
	freopen( "9.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 rt = read<i32>();
		ecnt = 0;
		memset( ehead, 0, sizeof(ehead[0]) * ( n + 5 ) );
		for( int i = 1; i <= n; i ++ ) {
			ci32 flag = read<i32>();
			if( flag ) {
				base[i] = 0;
				ci32 k = read<i32>();
				for( int j = 0; j < k; j ++ ) {
					ci32 w = read<i32>();
					ci32 u = read<i32>();
					add_edge( i, u, w );
				}
			}
			else {
				base[i] = read<i32>();
			}
		}
		cnt[rt] = 1;
		dfs(rt);
		i64 res = 0, max_item = 0;
		for( int i = ehead[rt]; i; i = e[i].next ) {
			res += f[ e[i].to ];
			chk_Max( max_item, f[ e[i].to ] );
		}
		if( res - max_item > MAX ) 
			printf( "Impossible\n" );
		else 
			printf( "%" PRId64 "\n", res - max_item );
	}
	
}
