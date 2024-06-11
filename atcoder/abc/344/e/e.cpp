/*
 * e.cpp 2024-03-11
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

std::map<i32, i32> nxt, pre;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	std::vector<i32> a(n);
	for( auto &x: a ) 
		x = read<i32>();
	for( int i = 0; i < n; i ++ ) {
		if( i != 0 ) 
			pre[ a[i] ] = a[ i - 1 ];
		else
			pre[ a[i] ] = 0;
		if( i != n - 1 ) 
			nxt[ a[i] ] = a[ i + 1 ];
		else
			nxt[ a[i] ] = 0;
	}
	i32 q = read<i32>();
	while( q -- ) {
		ci32 op = read<i32>();
		if( op == 1 ) {
			ci32 x = read<i32>();
			ci32 y = read<i32>();
			ci32 old = nxt[x];
			nxt[x] = y;
			pre[y] = x;
			nxt[y] = 0;
			if( old ) {
				nxt[y] = old;
				pre[old] = y;
			}
		}
		else {
			ci32 x = read<i32>();
			ci32 la = pre[x];
			ci32 nx = nxt[x];
			if( la ) 
				nxt[la] = nx;
			if( nx ) 
				pre[nx] = la;
			nxt.erase(x);
			pre.erase(x);
		}
	}
	for( auto &[x, y]: pre ) {
		if( y == 0 ) {
			i32 cur = x;
			while( cur ) {
				printf( "%d ", cur );
				cur = nxt[cur];
			}
			return 0;
		}
	}
}
