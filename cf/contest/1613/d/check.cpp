/*
 * check.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

const int N = 5e5 + 1e4;

int n;
int a[N], b[N];

bool check( int depth ) {
	std::map<int, bool> vis;
	for( int i = 0; i < depth; i ++ ) {
		vis[ b[i] ] = true;
		int res = -1;
		for( int i = 0; i < N; i ++ ) {
			if( !vis[i] ) {
				res = i;
				break;
			}
		}
		if( aabs( res - b[i] ) > 1 )
			return false;
	}
	for( int i = 0; i < depth; i ++ ) {
		printf( "%d ", b[i] );
	}
	printf( "\n" );
	return true;
}

void dfs( int cur, int depth ) {
	if( !check( depth ) ) 
		return ;
	for( int i = cur + 1; i <= n; i ++ ) {
		b[depth] = a[i];
		dfs( i, depth + 1 );
	}
}

int main() {
	n= read<int>();
	for( int i = 1; i <= n; i ++ )
		a[i] = read<int>();
	dfs( 0, 0 );
}
