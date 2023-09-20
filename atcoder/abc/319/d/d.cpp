/*
 * d.cpp 2023-09-09
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
typedef const long long cll;

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

bool check( cll limit, cll max_line, std::vector<int> &list ) {
	ll cur = 0, line = 1;
	for( auto &x: list ) {
		if( x > limit ) 
			return false;
		if( cur + x <= limit ) 
			cur += x + 1;
		else {
			line ++;
			cur = x + 1;
		}
	}

	return line <= max_line;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	cint n = read<int>();
	cint m = read<int>();

	std::vector<int> l(n);
	for( auto &x: l ) 
		x = read<int>();

	ll left = 1, rig = 1e18, res = 1e18;
	while( left <= rig ) {
		cll mid = ( left + rig ) >> 1LL;
		if( check( mid, m, l ) ) {
			res = mid;
			rig = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	while( res > 1 && check( res - 1, m, l ) ) 
		res --;

	printf( "%lld\n", res );
	
}
