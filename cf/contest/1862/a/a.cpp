/*
 * a.cpp 2023-08-24
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
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();
		std::vector<std::vector<bool>> vis( m + 1, std::vector<bool>(26) );
		for( int i = 1; i <= n; i ++ ) {
			char input[30];
			scanf( "%s", input + 1 );
			for( int j = 1; j <= m; j ++ ) {
				vis[j][ input[j] - 'a' ] = true;
			}
		}

		int flag = 0;
		for( int i = 1; i <= m; i ++ ) {
			if( flag == 0 && vis[i][ 'v' - 'a' ] ) {
				flag ++;
				continue;
			}
			if( flag == 1 && vis[i][ 'i' - 'a' ] ) {
				flag ++;
				continue;
			}
			if( flag == 2 && vis[i][ 'k' - 'a' ] ) {
				flag ++;
				continue;
			}
			if( flag == 3 && vis[i][ 'a' - 'a' ] ) {
				flag ++;
				continue;
			}
		}

		printf( "%s\n", flag == 4? "YES": "NO" );
	}
}
