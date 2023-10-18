/*
 * d.cpp 2023-09-28
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	
	while( T -- ) {
		cint n = read<int>();
		cint m = read<int>();

		static char str[N];
		static int p[N];
		scanf( "%s", str );
		cint len = strlen(str);
		for( int i = 0; i < len; i ++ ) {
			p[i] = ( str[i] - '0' );
		}

		bool solved = false;
		for( int o = 1; o <= 9; o ++ ) {
			std::vector<int> a, b;
			a.push_back(o);
			int k = 0;
			bool flag = true;
			auto try_get = [&]( cint another ) {
				if( another == 0 ) {
					if( p[k] == 0 ) {
						k ++;
						return 0;
					}
					else {
						flag = false;
						return 0;
					}
				}
				if( p[k] == 0 ) {
					k ++;
					return 0;
				}
				if( p[k] >= another ) {
					if( k >= len || p[k] % another != 0 ) {
						flag = false;
						return 0;
					}
					cint res = p[k] / another;
					k ++;
					return res;
				}
				else {
					cint cur = p[k] * 10 + p[ k + 1 ];
					if( k + 1 >= len || cur % another != 0 ) {
						flag = false;
						return 0;
					}
					k += 2;
					return cur / another;
				}
				return 0;
			};
			for( int j = 1; j <= m; j ++ ) {
				b.push_back(try_get(a[0]));
				if( !flag )
					break;
			}
			for( int i = 1; i < n; i ++ ) {
				a.push_back(try_get(b[0]));
				if( !flag )
					break;
				for( int j = 1; j < m; j ++ ) {
					if( a[i] == 0 && p[k] == 0 ) {
						k ++;
						continue;
					}
					if( b[j] != try_get( a[i] ) ) {
						flag = false;
						break;
					}
					if( !flag )
						break;
				}
			}

			if( k < len ) 
				flag = false;
			if( flag ) {
				for( auto &x: a ) 
					printf( "%d", x );
				printf( " " );
				for( auto &x: b)  
					printf( "%d", x );
				solved = true;
				printf( "\n" );
				break;
			}
		}

		if( !solved ) 
			printf( "Impossible\n" );

	}
}
