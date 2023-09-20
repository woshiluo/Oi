/*
 * e.cpp 2023-09-18
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

#include <random>
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

const int N = 5100;
const int M = 8192;

std::random_device seed;
std::mt19937 rnd(seed());

void work() {
	cint n = read<int>();
	std::vector<int> b( n + 1 );
	static short mex[N][N];
	static bool f[N][M];
	for( int i = 1; i <= n; i ++ ) 
		b[i] = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		std::vector<bool> vis(M, 0);
		int cur = 0;
		for( int j = i; j <= n; j ++ ) {
			vis[ b[j] ] = true;
			while( vis[cur] ) 
				cur ++;
			mex[i][j] = cur;
		}
	}

	f[0][0] = 1;
	for( int i = 1; i <= n; i ++ ) { 
		std::vector<int> lst(M, -1);
		for( int j = 0; j < M; j ++ ) 
			f[i][j] = f[ i - 1 ][j];
		for( int j = 1; j <= i; j ++ ) 
			lst[ mex[j][i] ] = j;
		std::vector<int> list;
		for( int j = 0; j < M; j ++ ) 
			if( lst[j] != -1 ) 
				list.push_back(j);

		std::shuffle( list.begin(), list.end(), rnd );

		cint size = list.size();
		for( int j = 0; j < Min( size, 30 ); j ++ ) {
			cint p = list[j];
			for( int k = 0; k < M; k ++ ) 
				f[i][k] |= f[ lst[p] - 1 ][ k ^ p ];
		}
	}

	for( int i = M - 1; i >= 0; i -- ) 
		if( f[n][i] ) {
			printf( "%d\n", i );
			return ;
		}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		work();
	}
}
