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

#include <vector>
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

int main() {
	const int n = read<int>();
	int k = read<int>();
	const int x = read<int>();
	std::vector<int> a;

	for( int i = 1; i <= n; i ++ ) {
		a.push_back( read<int>() );
	}
	std::sort( a.begin(), a.end() );
	for( auto &item: a ) {
		const int t = Min( k, item / x );
		k -= t; item -= t * x;
	}
	if( k != 0 ) {
		std::sort( a.begin(), a.end(), []( const int &_a, const int &_b ) { return _a > _b; } );
		for( auto &item: a ) {
			k --;
			item = 0;
			if( k == 0 ) 
				break;
		}
	}
	ll ans = 0;
	for( auto &item: a ) {
		ans += item;
	}
	printf( "%lld\n", ans );
}
