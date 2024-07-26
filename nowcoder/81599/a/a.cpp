/*
 * a.cpp 2024-07-25
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

const int N = 1e6 + 5;

struct Set {
	int set[N], size[N], val[N], max[N];
	void init( ci32 n ) { 
		for( int i = 0; i <= n; i ++ ) {
			set[i] = i; 
			size[i] = 1;
			val[i]  = 1;
			max[i] = 1;
		}
	}
	int get_fa( ci32 cur ) {
		if( set[cur] == cur )
			return cur;
		return get_fa( set[cur] );
	}
	int query( ci32 cur ) {
		if( set[cur] == cur )
			return val[cur];
		return val[cur] + query( set[cur] );
	}
	int& operator[]( const int cur ) { 
		return set[ get_fa(cur) ];
	}

	void merge( ci32 from, ci32 to ) {
		ci32 fu = get_fa(from), fv = get_fa(to);

		ci32 base = query(from);

		// fu -> fv
		if( size[fu] < size[fv] ) {
			set[fu] = set[fv];

			size[fv] += size[fu];

			val[fv] += base;
			val[fu] -= val[fv];

			max[fv] = Max( max[fu], base + max[fv] );
		}
		else {
			// fv -> fu
			set[fv] = set[fu];
			size[fu] += size[fv];

			val[fv] += base;
			val[fv] -= val[fu];

			max[fu] = Max( max[fu], base + max[fv] );
		}
	}
} set;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif


	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();

		set.init(n);

		for( int i = 1; i < n; i ++ ) {
			ci32 u = read<i32>();
			ci32 v = read<i32>();

			ci32 x = read<i32>();

			set.merge( u, v );
			
			printf( "%d ", set.max[ set[x] ] - 1 );
		}
		printf( "\n" );
	}
}
