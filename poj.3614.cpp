/*
 * poj.3614.cpp
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

cint N = 3100;
cint MAX_SPF = 1100;

struct Cow { int min, max; };

int pool[MAX_SPF];
Cow cows[N];

bool cmp( const Cow &_a, const Cow &_b ) { 
	if( _a.max == _b.max ) 
		return _a.min < _b.min;
	return _a.max < _b.max;
}

int main() {
	cint n = read<int>();
	cint m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		cows[i].min = read<int>();
		cows[i].max = read<int>();
	}
	std::sort( cows + 1, cows + n + 1, cmp );
	for( int i = 1; i <= m; i ++ ) {
		cint spf = read<int>();
		cint cover = read<int>();
		pool[spf] += cover;
	}

	int cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = cows[i].min; j <= cows[i].max; j ++ ) {
			if( pool[j] ) {
				pool[j] --;
				cnt ++;
				break;
			}
		}
	}
	printf( "%d\n", cnt );
}
