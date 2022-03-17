/*
 * d.cpp
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

const int N = 5e5 + 1e4;

int a[N];

inline int lowbit( const int cur ) { return cur & ( - cur ); }
struct BIT {
	int n;
	int tree[N];
	void init( int _n ) {
		n = _n;
		for( int i = 0; i <= n; i ++ ) {
			tree[i] = 0;
		}
	}
	void add( int pos, int val ) {
		for( ; pos <= n; pos += lowbit(pos) ) 
			tree[pos] += val;
	}
	int sum( int pos ) { 
		int res = 0;
		for( ; pos; pos -= lowbit(pos) ) {
			res += tree[pos];
		}
		return res;
	}
	int sum( int left, int rig ) {
		return sum(rig) - sum( left - 1 );
	}
} bit;

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		bit.init(n);
		ll res = 0;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			res += 1LL * bit.sum( a[i] + 1, n );
			bit.add( a[i], 1 );
		}
		for( int i = 1; i <= n; i ++ ) {
			if( bit.sum(i, i) > 1 ) 
				res = 2;
		}
		printf( "%s\n", ( res & 1LL )? "NO": "YES" );
	}
}
