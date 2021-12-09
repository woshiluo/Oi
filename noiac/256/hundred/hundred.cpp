/*
 * hundred.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

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
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 210;
const int M = 510;

struct Edge {
	int from, to, val;
} e[M];

int n, m, k, sum;

double gen( int cur ) {
	static int in[N], out[N];
	memset( in, 0, sizeof(in) );
	memset( out, 0, sizeof(out) );
	int res = 0, cnt = 0;
	for( int i = 1; i <= 20; i ++ ) {
		if( cur & ( 1 << ( i - 1 ) ) ) {
			in[ e[i].to ] ++;
			out[ e[i].from ] ++;
			res += e[i].val;
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( out[i] > 1 ) 
			return 0;
		if( in[i] == 0 ) 
			cnt ++;
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < in[i]; j ++ ) 
			res += ( n - j );
	}
	return (double)pow( (sum + res), k ) / (double)cnt;
}

int main() {
#ifdef woshiluo
	freopen( "hundred.in", "r", stdin );
	freopen( "hundred.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>(); k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		sum += tmp;
	}
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w;
		u = read<int>(); v = read<int>(); w = read<int>();
		e[i] = (Edge) { u, v, w };
	}

	double res = 0;
	for( int set = 1; set < ( 1 << 20 ); set ++ ) {
		chk_Max( res, gen(set) );
	}

	printf( "%.10lf", res );
}
