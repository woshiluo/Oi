/*
 * luogu.3812.cpp
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

const int MAX_LENGHT = 55;
struct LinearBase {
	ll a[MAX_LENGHT];
	bool vis[MAX_LENGHT];
	void add( ll cur ) {
		for( int i = MAX_LENGHT - 1; i >= 0; i -- )  {
			if( !( ( cur >> i ) & 1 ) )
				continue;
			if( vis[i] == false ) {
				vis[i] = true;
				a[i] = cur;
				break;
			}
			else
				cur ^= a[i];
		}
	}
	ll query( ll cur ) {
		for( int i = MAX_LENGHT - 1; i >= 0; i -- ) {
			if( vis[i] ) {
				if( ( cur ^ a[i] ) > cur ) 
					cur = ( cur ^ a[i] );
			}
		}
		return cur;
	}
} linearbase;

int n;

int main() {
#ifdef woshiluo
	freopen( "luogu.3812.in", "r", stdin );
	freopen( "luogu.3812.out", "w", stdout );
#endif
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		ll tmp = read<ll>();
		linearbase.add(tmp);
	}
	printf( "%lld\n", linearbase.query(0) );
}
