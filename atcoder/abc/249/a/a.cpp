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
	int a, b, c, d, e, f, x;
	a = read<int>(); b = read<int>(); c = read<int>(); d = read<int>(); e = read<int>(); f = read<int>(); x = read<int>();
	int fir = 0, sec = 0;
	{
		int tmp = x;
		int cur = 0;
		while( tmp > 0 ) {
			cur ++;
			tmp --;
			fir += b;
			if( cur == a ) {
				tmp -= c;
				cur = 0;
			}
		}
	}
	{
		int tmp = x;
		int cur = 0;
		while( tmp > 0 ) {
			cur ++;
			tmp --;
			sec += e;
			if( cur == d ) {
				tmp -= f;
				cur = 0;
			}
		}
	}
	if( fir == sec ) 
		printf( "Draw\n" );
	else 
		printf( "%s\n", fir > sec? "Takahashi": "Aoki" );
}
