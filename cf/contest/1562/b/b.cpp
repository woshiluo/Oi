/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cmath>
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

const int N = 1100;

bool vis[N];
char num[N][5];

bool is_prime( int cur ) {
	int sqrt = std::sqrt(cur);
	for( int i = 2; i <= sqrt; i ++ ) {
		if( cur % i == 0 ) 
			return false;
	}
	return true;
}

void split( int cur ) {
	int bit[10], cnt = 0, p = cur;
	while( p ) {
		bit[cnt] = ( p % 10 );
		p /= 10;
		cnt ++;
	}
	for( int i = 0; i < cnt; i ++ ) {
		num[cur][ cnt - i ] = ( bit[i] + '0' );
	}
}

void init() {
	for( int i = 1; i <= 1000; i ++ ) {
		vis[i] = is_prime(i);
		split(i);
	}
	vis[1] = false;
}

bool subcmp( char a[], char b[] ) {
	int alen = strlen( a + 1 ), blen = strlen( b + 1 );
	int p1 = 1, p2 = 1;
	while( p1 <= alen && p2 <= blen ) {
		if( a[p1] == b[p2] ) {
			p1 ++;
		}
		p2 ++;
	}
	return ( p1 == alen + 1 );
}

int try_min( char str[], int len ) {
	for( int i = 1; i <= 1000; i ++ ) {
		if( vis[i] ) 
			continue;
		if( subcmp( num[i], str ) )
			return i;
	}
	return 0;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	init();
	while( T -- ) {
		int k = read<int>();
		char str[110];
		scanf( "%s", str + 1 );
		int res = try_min( str, k );
		printf( "%ld\n", strlen( num[res] + 1 ) );
		printf( "%d\n", res );
	}
}
