/*
 * a1.cpp 2023-10-22
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

int work( std::vector<int> &a, std::vector<int> &b ) {
	cint n = a.size();
	int ans = 0;
	int p1 = 0, p2 = 0;
	int mn = n;
	while( p1 < mn && p2 < n ) {
		if( a[p1] < b[p2] ) {
			p1 ++;
			p2 ++;
		}
		else {
			p2 ++;
			mn --;
			ans ++;
		}
	}
	ans += Min( ( mn - p1 ), ( n - p2 ) );
	return ans;
}

int main() {
#ifdef woshiluo
	freopen( "a1.in", "r", stdin );
	freopen( "a1.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		std::vector<int> a( n - 1  ), b ( n );
		for( auto &x: a ) 
			x = read<int>();
		a.insert( a.begin(), 1 );
		for( auto &x: b ) 
			x = read<int>();
		std::sort( a.begin(), a.end() );
		a[0] = 1;
		std::sort( b.begin(), b.end() );
		cint ans = work( a, b );
		printf( "%d\n", ans );
	}
}
