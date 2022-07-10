/*
 * f.cpp
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

const int N = 2e5 + 1e4;

int pre[N], mid[N], rpr[N], rmi[N];
int son[N][2];

int len( cint left, cint rig ) { return rig - left + 1; }
bool is_in( cint from, cint to, cint pos ) { return from <= pos && pos <= to; }

void no_sol() {
	printf( "-1\n" );
	std::exit(0);
}

int dfs( cint pl, cint pr, cint ml, cint mr ) {
	if( pr < pl ) 
		return 0;
	if( len( pl, pr ) != len( ml, mr ) ) 
		no_sol();
	if( len( pl, pr ) == 1 && pre[pl] != mid[ml] ) 
		no_sol();
	if( len( pl, pr ) == 1 ) 
		return pre[pl];

	cint rt = pre[pl];
	cint pos = rmi[rt];

	if( !is_in( ml, mr, pos ) ) 
		no_sol();

	cint pmid = pl + len( ml, pos - 1 );
	son[rt][0] = dfs( pl + 1, pmid, ml, pos - 1 );
	son[rt][1] = dfs( pmid + 1, pr, pos + 1, mr );

	return rt;
}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	cint n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		pre[i] = read<int>();
		rpr[ pre[i] ] = i;
	}
	for( int i = 1; i <= n; i ++ ) {
		mid[i] = read<int>();
		rmi[ mid[i] ] = i;
	}

	int rt = dfs( 1, n, 1, n );

	if( rt != 1 ) 
		no_sol();

	for( int i = 1; i <= n; i ++ ) 
		printf( "%d %d\n", son[i][0], son[i][1] );
}
