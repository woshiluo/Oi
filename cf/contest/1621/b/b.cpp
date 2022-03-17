/*
 * b.cpp
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
T pow( T a, ll p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const ll N = 5e5 + 1e4;
const ll INF = 0x7f7f7f7f;

struct Node {
	ll l, r, c;
} a[N];

void calc() {
	ll n = read<ll>();
	ll cur_l = 0, cur_r = 0, cur_all = 0;
	for( ll i = 1; i <= n; i ++ ) {
		a[i].l = read<ll>(); a[i].r = read<ll>(); a[i].c = read<ll>();
	}
	for( ll i = 1; i <= n; i ++ ) {
		if( cur_l == 0 ) 
			cur_l = i;
		if( cur_r == 0 ) 
			cur_r = i;

		if( a[i].l < a[ cur_l ].l ) 
			cur_l = i;
		if( a[i].r > a[ cur_r ].r ) 
			cur_r = i;
		if( a[i].l == a[ cur_l ].l && a[i].c < a[cur_l].c ) 
			cur_l = i;
		if( a[i].r == a[ cur_r ].r && a[i].c < a[cur_r].c ) 
			cur_r = i;

		if( !( a[cur_all].l == a[cur_l].l && a[cur_all].r == a[cur_r].r ) )
			cur_all = 0;
		if( a[i].l == a[cur_l].l && a[i].r == a[cur_r].r && a[i].c <= ( cur_all == 0? INF: a[cur_all].c )  )
			cur_all = i;

		printf( "%lld\n", Min( a[cur_l].c + a[cur_r].c, cur_all == 0? INF: a[cur_all].c ) );
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	ll T = read<ll>();
	while( T -- ) {
		calc();
	}
}
