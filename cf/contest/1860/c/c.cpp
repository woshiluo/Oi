/*
 * c.cpp 2023-08-19
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

const int N = 3e5 + 1e4;
const int INF = 0x3f3f3f3f;

inline int lowbit( const int cur ) { return cur & ( -cur ); }
struct BIT {
	int n;
	int tree[N];

	void init( cint _n ) {
		n = _n;
		for( int i = 0; i <= _n; i ++ ) {
			tree[i] = INF;
		}
	}
	void min( int cur, cint val ) {
		for( ; cur <= n; cur += lowbit(cur) ) 
			chk_Min( tree[cur], val );
	}

	int query( int cur ) {
		int res = INF;
		for( ; cur; cur -= lowbit(cur) ) 
			chk_Min( res, tree[cur] );
		return res;
	}
} bit;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif

	int T = read<int>();

	while( T -- ) {
		cint n = read<int>();

		bit.init(n);
		std::vector<int> p(n + 1);

		for( int i = 1; i <= n; i ++ ) 
			p[i] = read<int>();

		int cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			int min = bit.query( p[i] );

			if( min == INF ) {
				bit.min( p[i], 1 );
				continue;
			}
			if( min == 1 ) {
				cnt ++;
				bit.min( p[i], 0 );
			}
			else {
				bit.min( p[i], 1 );
			}
		}

		printf( "%d\n", cnt );
	}
}
