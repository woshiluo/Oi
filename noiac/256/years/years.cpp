/*
 * years.cpp
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

#include <map>
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

const int N = 1e6 + 1e5;
const int INF = 0x3f3f3f3f;

int n;
int a[N];

namespace pub {
	int dp() {
		static int pos[N];
		memset( pos, INF, sizeof(pos) );
		pos[0] = 0;
		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			int cur = std::lower_bound( pos, pos + res + 1, a[i] ) - pos - 1;
			chk_Max( res, cur + 1 );
			chk_Min( pos[ cur + 1 ], a[i] );
		}
		return res;
	}
}

namespace sub1 {
	double dp( const int k ) {
		static int f[N]; 
		static double g[N];
		int max_f = 0;
		double res = 0;
		for( int i = 0; i <= n; i ++ ) {
			f[i] = 0; g[i] = 0;
		}
		for( int i = 1; i <= n; i ++ ) {
			f[i] = 1;
			for( int j = 1; j < i; j ++ ) {
				if( a[i] > a[j] ) {
					if( f[j] + 1 == f[i] ) {
						chk_Max( g[i], g[j] + std::log( (double)( a[i] - a[j] + k ) ) );
					}
					if( f[j] + 1 > f[i] ) {
						f[i] = f[j] + 1;
						g[i] = g[j] + std::log( (double)( a[i] - a[j] + k ) );
					}
				}
			}
			if( f[i] == max_f ) 
				chk_Max( res, g[i] );
			if( f[i] > max_f ) {
				max_f = f[i];
				res = g[i];
			}
		}
		return res;
	}
	void calc() {
		printf( "%d\n", pub::dp() );
		int q = read<int>();
		while( q -- ) {
			int k = read<int>();
			printf( "%.10lf\n", dp(k) );
		}
	}
}

namespace sub2 {
	double dp( const int k ) {
		static int pos[N];
		std::map<int, double> mp[N];
		memset( pos, INF, sizeof(pos) );
		pos[0] = 0;
		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			int cur = std::lower_bound( pos, pos + res + 1, a[i] ) - pos - 1;
			chk_Max( res, cur + 1 );
			chk_Min( pos[ cur + 1 ], a[i] );
			double tmp = 0;
			for( auto x: mp[cur] ) {
				int la = x.first;
				double val = x.second;
				if( la >= a[i] )
					break;
				chk_Max( tmp, val + std::log( (double) ( a[i] - la + k ) ) );
			}
			mp[ cur + 1 ][ a[i] ] = tmp;
		}

		double ans = 0;
		for( auto x: mp[res] ) 
			chk_Max( ans, x.second );
		return ans;
	}
	void calc() {
		printf( "%d\n", pub::dp() );
		int q = read<int>();
		while( q -- ) {
			int k = read<int>();
			printf( "%.10lf\n", dp(k) );
		}
	}
} 

int main() {
#ifdef woshiluo
	freopen( "years.in", "r", stdin );
	freopen( "years.out", "w", stdout );
#endif
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	if( n <= 20000 ) 
		sub1::calc();
	else 
		sub2::calc();
}
