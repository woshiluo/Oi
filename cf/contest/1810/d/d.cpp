/*
 * d.cpp 2023-08-26
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
typedef const long long cll;

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

bool check( cll fl, cll fr, cll sl, cll sr ) { return fl <= sl && sr <= fr; }
bool vaild( cll fl, cll fr, cll sl, cll sr ) { return Max( fl, sl ) <= Min( fr, sr ); }

void work() {
	int q = read<int>();
	ll left = 0, rig = 1e18 + 1;
	while( q -- ) {
		cint op = read<int>();
		if( op == 1 ) {
			cint a = read<int>();
			cint b = read<int>();
			cint n = read<int>() - 1;
			if( n == 0 ) {
				if( left == 0 || vaild( 1, a, left, rig ) ) {
					printf( "1 " );
					chk_Max( left, 1LL );
					chk_Min( rig, (ll)a );
				}
				else 
					printf( "0 " );
			}
			else {
				cll cleft = 1LL * ( a - b ) * n + b + 1;
				cll crig = 1LL * ( a - b ) * n + a;

				if( left == 0 || vaild( cleft, crig, left, rig ) ) {
					printf( "1 " );
					chk_Max( left, cleft );
					chk_Min( rig, crig );
				}
				else 
					printf( "0 " );

			}
		}
		if( op == 2 ) {
			cint a = read<int>();
			cint b = read<int>();

			if( left == 0 ) {
				printf( "-1 " );
				continue;
			}
			if( check( 1, a, left, rig ) ) {
				printf( "1 " );
				continue;
			}

			cll k = ( left - a ) / ( a - b ) - ( ( left - a ) % ( a - b ) == 0 );
			cll cleft = k * ( a - b ) + a + 1;
			cll crig = ( k + 1 ) * ( a - b ) + a;
			if( check( cleft, crig, left, rig ) ) {
				printf( "%lld ", k + 2 );
			}
			else {
				printf( "-1 " );
			}
		}
	}
	printf( "\n" );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		work();
	}
}
