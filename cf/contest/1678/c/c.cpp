/*
 * c.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <set>
#include <algorithm>

typedef const int cint;
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
	for (; isdigit(ch) == 0; ch = getchar())
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

const int N = 5100;

inline int lowbit( cint cur ) { return cur & ( -cur); }

struct BIT {/*{{{*/
	int tree[N];

	BIT() { memset( tree, 0, sizeof(tree) ); }

	void add( int pos, cint val ) {
		for( ; pos < N; pos += lowbit(pos) ) 
			tree[pos] += val;
	}

	int pre( int pos ) {
		if( pos <= 0 ) 
			return 0;
		int res = 0;
		for( ; pos; pos -= lowbit(pos) ) 
			res += tree[pos];
		return res;
	}

	int suf( int pos ) {
		return pre( N - 1 ) - pre( pos - 1 );
	}
};/*}}}*/

int val[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			val[i] = read<int>();
		}

		BIT bit[2];
		ll ans = 0;
		for( int a = 1; a <= n; a ++ ) {
			for( int i = a + 1; i <= n; i ++ ) 
				bit[1].add( val[i], 1 );
			int res = 0;
			for( int c = a + 1; c <= n; c ++ ) {
				bit[1].add( val[c], -1 );
				res -= bit[0].suf( val[c] + 1 );

				if( val[a] < val[c] )
					ans += res;

				bit[0].add( val[c], 1 );
				res += bit[1].pre( val[c] - 1 );
			}

			for( int i = a + 1; i <= n; i ++ ) 
				bit[0].add( val[i], -1 );
		}
		printf( "%lld\n", ans );
	}
}
