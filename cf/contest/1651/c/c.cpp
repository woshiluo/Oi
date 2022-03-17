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

#include <vector>
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

const int N = 2e5 + 1e4;

ll a[N], b[N], c[N], d[N];

int full_pow( const int cur ) { return 1 << cur; }
bool chk_pos( const int cur, const int k ) { return ( cur >> k ) & 1; }

template <class T>
T aabs( T _a ) { return _a < 0? -_a: _a; }
ll get_ans( int i, int j ) { return aabs( a[i] - b[j] ); }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			c[i] = a[i];
		}
		for( int i = 1; i <= n; i ++ ) {
			b[i] = read<int>();
			d[i] = b[i];
		}
		std::sort( c + 1, c + n + 1 );
		std::sort( d + 1, d + n + 1 );
		ll ans = get_ans( 1, 1 ) + get_ans( n, n );
		for( int s = 0; s < full_pow(4); s ++ ) {
			std::vector<bool> vis;
			ll res = 0;
			vis.resize(4);
			for( int j = 0; j < 4; j ++ ) {
				if( chk_pos( s, j ) ) {
					if( j == 0 ) {
						vis[0] = vis[2] = true;
						res += get_ans( 1, 1 );
					}
					if( j == 1 ) {
						vis[0] = vis[3] = true;
						res += get_ans( 1, n );
					}
					if( j == 2 ) {
						vis[1] = vis[2] = true;
						res += get_ans( n, 1 );
					}
					if( j == 3 ) {
						vis[1] = vis[3] = true;
						res += get_ans( n, n );
					}
				}
			}
			c[0] = d[0] = c[ n + 1 ] = d[ n + 1 ] = (ll)(1e12);
			for( int i = 0; i < 4; i ++ ) {
				if( !vis[i] ) {
					if( i == 0 ) {
						ll tmp = get_ans( 1, 1 );
						for( int j = 2; j <= n; j ++ )
							chk_Min( tmp, get_ans( 1, j ) );
						res += tmp;
					}
					if( i == 1 ) {
						ll tmp = get_ans( n, 1 );
						for( int j = 2; j <= n; j ++ )
							chk_Min( tmp, get_ans( n, j ) );
						res += tmp;
					}
					if( i == 2 ) {
						ll tmp = get_ans( 1, 1 );
						for( int j = 2; j <= n; j ++ )
							chk_Min( tmp, get_ans( j, 1 ) );
						res += tmp;
					}
					if( i == 3 ) {
						ll tmp = get_ans( 1, n );
						for( int j = 2; j <= n; j ++ )
							chk_Min( tmp, get_ans( j, n ) );
						res += tmp;
					}
				}
			}
			chk_Min( ans, res );
		}
		printf( "%lld\n", ans );
	}
}
