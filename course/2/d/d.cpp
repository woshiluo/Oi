/*
 * d.cpp 2024-01-04
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

const int N = 1e5 + 1e4;

i64 tot[N], get[N];
i32 id[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	for( int i = 1; i <= n; i ++ ) {
		ci32 k = read<i32>();
		for( int j = 1; j <= k; j ++ ) {
			ci32 cur = read<i32>();
			ci32 out = read<i32>();
			tot[cur] += out;
			get[cur] ++;
			tot[i] -= out;
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		id[i] = i;
	}
	std::sort( id + 1, id + n + 1, []( const int &_a, const int &_b ) {
			if( tot[_a] == tot[_b] ) 
				if( get[_a] == get[_b] )
					return _a < _b;
				else
					return get[_a] > get[_b];
			else 
				return tot[_a] > tot[_b];
	});
	for( int i = 1; i <= n; i ++ ) 
		printf( "%d %.2lf\n", id[i], (double)tot[ id[i] ] / 100 );
}
