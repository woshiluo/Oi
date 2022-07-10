/*
 * e.cpp
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

#include <map>
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

const int N = 1e5 + 1e4;

int s[N], x[N];

int main() {
	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i < n; i ++ ) {
		s[i] = read<int>();
	}
	for( int i = 1; i <= m; i ++ ) {
		x[i] = read<int>();
	}

	std::vector<ll> list[2];

	list[1].push_back(0);
	for( int i = 2; i <= n; i ++ ) {
		cint p = ( i & 1 );
		list[p].push_back( (ll)s[ i - 1 ] - list[ p ^ 1 ].back() );
	}

	std::map<ll, int> mp;
	std::map<ll, int> pool[2], sum;

	for( auto &val: list[0] ) {
		pool[0][val] ++;
	}
	for( auto &val: list[1] ) 
		pool[1][val] ++;

	for( int i = 1; i <= m; i ++ ) {
		for( auto &pair: pool[0] ) {
			sum[ pair.first - x[i] ] += pair.second;
		}
		for( auto &pair: pool[1] ) {
			sum[ x[i] - pair.first ] += pair.second;
		}
	}

	int res = 0;
	for( auto &pair: sum ) 
		chk_Max( res, pair.second );
	printf( "%d\n", res );
}
