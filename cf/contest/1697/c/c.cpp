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

const int N = 1e5 + 1e4;

int main() {
	int T = read<int>();
	while( T -- ) {
		static char a[N], b[N];
		static int sum_a[N], sum_b[N];
		static int pool[3];
		pool[0] = pool[1] = pool[2] = 0;

		cint n = read<int>();
		scanf( "%s", a + 1 );
		scanf( "%s", b + 1 );
		for( int i = 1; i <= n; i ++ ) {
			sum_a[i] = sum_a[ i - 1 ] + a[i];
		}
		for( int i = 1; i <= n; i ++ ) {
			sum_b[i] = sum_b[ i - 1 ] + b[i];
		}

		bool flag = ( sum_a[n] == sum_b[n] ), checking = false;
		int st = n + 1;
		for( int i = 1; i <= n; i ++ ) {
			if( !checking && a[i] == b[i] ) 
				continue;
			chk_Min( st, i );
			checking = true;
			pool[ a[i] - 'a' ] ++;
			if( sum_a[i] == sum_b[i] && checking ) {
				int cur = ( a[i] - 'a' );
				checking = false;

				int cnt = ( pool[0] != 0 ) + 
					( pool[1] != 0 ) +
					( pool[2] != 0 );

				for( int k = 0; k < 3; k ++ ) {
					std::vector<int> list[2];
					for( int j = st; j <= i; j ++ ) {
						if( ( a[j] - 'a' ) == k )
							list[0].push_back(j);
					}
					for( int j = st; j <= i; j ++ ) {
						if( ( b[j] - 'a' ) == k )
							list[1].push_back(j);
					}

					cint size = list.size();
					for( int i = 0; i < size; i ++ ) {
						if( list[1]
					}
				}

				flag = false;
				break;
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
