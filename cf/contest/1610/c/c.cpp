/*
 * c.cpp
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

struct Friend { int a, b; };

std::vector<Friend> fri;

bool check( int cur ) {
	int p = 0;
	for( auto &f: fri ) {
		if( f.a >= p && f.b >= cur - p - 1 )
			p ++;
		if( p == cur ) 
			return true;
	}
	return false;
}

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		fri.clear();
		for( int i = 1; i <= n; i ++ ) {
			int a, b;
			a = read<int>(); b = read<int>();
			fri.push_back( (Friend){ b, a } );
		}

		int left = 1, rig = n, res = 1; 
		while( left <= rig ) {
			int mid = ( left + rig ) >> 1;
			if( check(mid) ) {
				res = mid;
				left = mid + 1;
			}
			else
				rig = mid - 1;
		}
		printf( "%d\n", res );
	}
}
