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

#include <set>
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

const int N = 1100;

int a[N], b[N];

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		std::set<int> set;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			set.insert(i);
		}
		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			auto p = set.begin();
			while( p != set.end() && *p == a[i] ) 
				p ++;
			if( p == set.end() ) {
				flag = false;
				break;
			}
			b[i] = *p;
			set.erase( b[i] );
			if( i == n - 1 ) {
				if( *set.begin() == a[n] ) {
					b[n] = b[i];
					b[i] = a[n];
					break;
				}
			}
		}
		if( !flag ) {
			printf( "-1\n" );
			continue;
		}
		for( int i = 1; i <= n; i ++ ) 
			printf( "%d ", b[i] );
		printf( "\n" );
	}
}
