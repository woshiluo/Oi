/*
 * c.cpp 2024-03-10
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


const int N = 1e6 + 1e5;

i32 a[N];

int full_pow( ci32 cur ) { return 1 << cur; }
int full_mask( ci32 cur ) { 
	if( cur < 0 ) 
		return 0;
	return full_pow(cur + 1) - 1;
}
int chk_pos( ci32 cur, ci32 k ) { return ( cur >> k ) & 1; }

inline int lowbit( ci32 cur ) { return cur & ( - cur ); }

struct BIT {
	i64 tree[N];
	void add( i32 pos, ci32 val ) {
		pos += 1;
		for( ; pos < N; pos += lowbit(pos) )
			tree[pos] += val;
	}
	i64 query( i32 pos ) {
		pos += 1;
		if( pos <= 0 ) 
			return 0;
		i64 res = 0;
		for( ; pos; pos -= lowbit(pos) )
			res += tree[pos];
		return res;
	}
} bit;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 q = read<i32>();
	for( int i = 0; i < n; i ++ ) {
		a[i] = read<i32>();
		bit.add( i, a[i] );
	}

	for( int _ = 1; _ <= q; _ ++ ) {
		ci32 op = read<i32>();
		ci32 cur = read<i32>();
		ci32 x = read<i32>();
		if( op == 1 ) {
			bit.add( cur, x - a[cur] );
			a[cur] = x;
			continue;
		}
		i32 prefix = 0;
		i64 ans = 0;
		for( int k = 30; k >= 0; k -- ) {
			if( chk_pos( x, k ) ) {
				ci32 l = ( prefix ^ cur ) & ( ~full_mask( k - 1 ) );
				ci32 r = l | full_mask( k - 1 );
				ans += bit.query(r) - bit.query( l - 1 );
				prefix |= full_pow(k);
			}
		}
		ans += a[x ^ cur];
		printf( "%lld\n", ans );
	}
}
