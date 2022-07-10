/*
 * a.cpp
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

ll reverse( ll cur ) {
	int cnt = 0;
	static int pool[30];
	while( cur ) {
		pool[cnt] = ( cur % 10 );
		cnt ++;
		cur /= 10;
	}

	ll res = 0;
	for( int i = 0; i < cnt; i ++ ) 
		res = res * 10 + pool[i];

	return res;
}

ll chk( const ll max, ll cur ) {
	int res = 0;
	while( cur <= max ) {
		res ++;
		cur *= 10;
	}
	return res;
}

int main() {
	const ll n = read<ll>();
	const ll k = read<ll>();

	ll res = 0;
	if( k <= reverse(k) ) {
		res += chk( n, reverse(k) );
		if( k != reverse(k) )
			res += chk( n, k );
	}
	printf( "%lld\n", res );
}
