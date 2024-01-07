/*
 * e.cpp 2023-12-28
 *
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
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

struct Edge {
	i32 to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
void add_edge( ci32 cur, ci32 to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

double res = 0;
double val[N], f[N], r;

void dfs( ci32 cur ) {
	if( ehead[cur] == 0 ) {
		f[cur] *= val[cur];
		res += f[cur];
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		f[ e[i].to ] = f[cur] * r;
		dfs( e[i].to );
	}
}


int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	i32 n;
	double z;
	scanf( "%d%lf%lf", &n, &z, &r );
	r /= 100;
	r = 1 - r;
	for( int i = 0; i < n; i ++ ) {
		ci32 p = read<i32>();
		if( p == 0 ) {
			scanf( "%lf", &val[i] );
		}
		else {
			for( int j = 1; j <= p; j ++ ) {
				add_edge( i, read<i32>() );
			}
		}
	}
	f[0] = z;
	dfs(0);

	printf( "%d\n", (int)res );
}
