/*
 * a.cpp
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

int n;
std::vector<int> a;

void f( int p ) {
	if( a[ p + 1 ] < a[p] )
		std::swap( a[ p + 1 ], a[p] );
}

bool check() {
	for( int i = 2; i <= n; i ++ ) {
		if( a[i] < a[ i - 1 ] ) 
			return false;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		a.clear();

		n = read<int>();
		a.push_back(0);
		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			a.push_back(tmp);
		}
		int cnt = 0;
		while( !check() ) {
			cnt ++;
			if( cnt & 1 ) {
				for( int i = 1; i <= n - 2; i += 2 ) {
					f(i);
				}
			}
			else {
				for( int i = 2; i <= n - 1; i += 2 ) {
					f(i);
				}
			}
		}
		printf( "%d\n", cnt );
	}
}
