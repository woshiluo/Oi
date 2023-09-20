/*
 * spoj.3110.cpp
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

ll pow10[50];

int int_len( ll cur ) {
	int res = 0;
	while( cur ) {
		res ++;
		cur /= 10;
	}
	return res;
}

int get_pos( ll cur, int pos ) {
	int res = 0;
	while( pos ) {
		pos --;
		res = ( cur % 10 );
		cur /= 10;
	}
	return res;
}

int len_allow( int cur ) {
	return ( cur / 2 ) + ( cur & 1 );
}

void check( int bit[], int len ) {
	int cnt = 0;
	for( int i = 1; i <= len; i ++ ) {
		if( bit[i] > 18 ) 
			return ;
		if( bit[i] != bit[ i - 1 ] )
			cnt ++;
	}
	if( cnt == 1 ) {
		for( int i = 1; i <= 9; i ++ ) {
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "spoj.3110.in", "r", stdin );
	freopen( "spoj.3110.out", "w", stdout );
#endif
	int T = read<int>();
	pow10[1] = 1;
	for( int i = 2; i <= 20; i ++ ) {
		pow10[i] = pow10[ i - 1 ] * 10LL;
	}
	while( T -- ) {
		ll n = read<ll>();
		int len = int_len(n);
		for( int i = 1; i <= len; i ++ ) {
			bit[i] = ( n % 10 );
			n /= 10;
		}
		for( int sta = 0; sta <= full_pow(len); sta ++ ) {
			ll cur = n;
			for( int i = 1; i <= len; i ++ ) {
				if( sta & ( 1 << ( i - 1 ) ) ) {
					bit[i] += 10;
					bit[ i + 1 ] -= 1;
				}
			}
			check(bit);
			for( int i = 1; i <= len; i ++ ) {
				if( sta & ( 1 << ( i - 1 ) ) ) {
					bit[i] -= 10;
					bit[ i + 1 ] += 1;
				}
			}
		}

	}
}
