/*
 * tree.cpp
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

const int N = 1100;

int mp[N][N], line[N];
double ans[N][N];

double calc( const int n ) {
	double res = 0;
	for( int i = 4; i <= n; i ++ ) {
		double tmp = 1;
		for( int j = n - 2 - ( i - 2 ) + 1; j <= n - 2; j ++ ) 
			tmp = tmp * j / n;
		res += tmp * i * ( i - 3 ) / n;
	}

	return res;
}

int main() {
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );

	int n = read<int>();
	int sum = 0;
	for( int i = 1; i < n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			mp[i][j] = mp[j][i] = read<int>();
			line[i] += mp[i][j];
			line[j] += mp[j][i];
			sum += mp[i][j];
		}
	}

	double p1 = 2.0/(double)n,
		   p2 = 1.0/(double)n,
		   p3 = calc(n);
	int all_tree = ( n - 2 ) * ( n - 3 ) / 2;

	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			double &res = ans[i][j];

			res += p1 * mp[i][j] + p2 * ( line[i] + line[j] - mp[i][j] * 2 );
			if( all_tree )
				res += ( p3 * ( sum - line[i] - line[j] + mp[i][j] ) / all_tree );
			ans[j][i] = res;
		}
	}

	int k = read<int>();
	if( k != 2 ) {
		int u, v;
		u = read<int>(); v = read<int>();
		printf( "%.5lf\n", ans[u][v] );
	}
	else {
		for( int i = 1; i < n; i ++ ) {
			for( int j = i + 1; j <= n; j ++ ) {
				printf( "%.5lf ", ans[i][j] );
			}
			printf( "\n" );
		}
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
