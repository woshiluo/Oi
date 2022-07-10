/*
 * c.cpp
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

const int N = 30;

int pool[N];
int len[N];
char str[N][N];
bool vis[N][N];

inline int full_pow( const int cur ) { return 1LL << cur; }
inline bool chk_pos( const int cur, const int p ) { return cur & full_pow(p); }

int main() {
	int n, k;
	n = read<int>();
	k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", str[i] );
		len[i] = strlen( str[i] );
		for( int j = 0; j < len[i]; j ++ ) {
			str[i][j] -= 'a';
			vis[i][ (int)str[i][j] ] = true;
		}
	}

	int res = 0;
	for( int i = 0; i < full_pow(n); i ++ ) {
		for( int j = 1; j <= n; j ++) {
			if( chk_pos( i, j - 1 ) ) {
				for( int p = 0; p < 26; p ++ ) {
					pool[p] += vis[j][p];
				}
			}
		}
		int cnt = 0;
		for( int j = 0; j < 26; j ++ ) {
			if( pool[j] == k ) 
				cnt ++;
			pool[j] = 0;
		}
		chk_Max( res, cnt );
	}

	printf( "%d\n", res );
}
