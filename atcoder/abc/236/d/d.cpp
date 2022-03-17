/*
 * d.cpp
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

const int N = 20;

int a[N][N];
bool has[ 1 << N ];

std::vector<std::vector<int>> b[3];

int full_pow( int cur ) { return 1 << cur; }
int check_pos( int cur, int pos ) { return ( cur >> pos ) & 1; }
int pop_2( int cur ) {
	int cnt = 0;
	while( cur ) {
		cnt += ( cur & 1 );
		cur >>= 1;
	}
	return cnt;
}

int n, n2, ans = 0;

std::vector<int> d;
bool vis[N];
void dfs( int depth, std::vector<int> &p1, std::vector<int> &p2, int cur ) {
	if( depth == n + 1 ) {
		chk_Max( ans, cur );
		return ;
	} 
	for( int i = 0; i < n; i ++ ) {
		if( !vis[i] && p1[depth - 1] < p2[i] ) {
			vis[i] = true;
			dfs( depth + 1, p1, p2, cur ^ ( a[ p1[depth - 1] ][ p2[i] ] ) );
			vis[i] = false;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	n = read<int>();
	n2 = ( n << 1 );
	for( int i = 1; i <= n2; i ++ ) {
		for( int j = i + 1; j <= n2; j ++ ) {
			a[i][j] = a[j][i] = read<int>();
		}
	}
	int full = full_pow(n2) - 1;
	for( int i = 0; i < full_pow(n2); i ++ ) {
		if( has[i] || has[ full ^ i ] ) 
			continue;
		has[i] = has[ full ^ i ] = true;
		if( pop_2(i) == n ) {
			std::vector<int> res, oth;
			for( int j = 0; j < n2; j ++ ) {
				if( check_pos(i, j) ) 
					res.push_back( j + 1 );
				else
					oth.push_back( j + 1 );
			}
			b[0].push_back(res);
			b[2].push_back(oth);
		}
	}

	int p = 0;
	for( auto &p1: b[0] ) {
		dfs( 1, p1, b[2][p], 0 );
		dfs( 1, b[2][p], p1, 0 );
		p ++;
	}
	printf( "%d\n", ans );
}
