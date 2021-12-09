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

const int N = 220;
const int BASE = 110;

int a[N], b[N], cnt[N], cnt2[N];

bool work() {
	memset( cnt, 0, sizeof(cnt) );
	memset( cnt2, 0, sizeof(cnt2) );
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		a[i] += BASE;
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
		b[i] += BASE;
		cnt[ b[i] - 1 ] ++;
	}
	std::sort( a + 1, a + n + 1 );
	int p = 0, k = 0;
	for( int i = 1; i <= n; i ++ ) {
		while( p != a[i] ) {
			int min = Min( cnt2[p], k );
			cnt2[p] -= min; k -= min;

			min = Min( cnt[p], k );
			cnt[p] -= min; k -= min;

			if( cnt2[p] || k ) 
				return false;
			cnt2[ p + 1 ] += cnt[p];
			p ++; k = 0;
		}
		k ++;
	}
	int min = Min( cnt2[p], k );
	cnt2[p] -= min; k -= min;

	min = Min( cnt[p], k );
	cnt[p] -= min; k -= min;

	if( cnt2[p] || k ) 
		return false;
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}

