/*
 * a.cpp 2023-09-26
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

struct Edge {
	int ecnt, to, next;
} e[N];
int ehead[N], ecnt;
void add_edge( cint cur, cint to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int f[N];

int dfs( cint cur ) {
	std::vector<int> list;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		cint to = e[i].to;
		list.push_back( dfs(to) );
	}
	std::sort( list.begin(), list.end() );
	cint size = list.size();;
	if( size == 0 )
		return 1;
	if( size == 1 ) 
		return list[0];
	if( list[ size - 1 ] != list[ size - 2 ] )
		return list.back();
	else
		return list.back() + 1;
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		ecnt = 0;
		memset( ehead, 0, sizeof(int) * ( n + 1 ) );
		for( int i = 1; i <= n; i ++ ) {
			cint fa = read<int>();;
			if( fa == 0 ) 
				continue;
			add_edge( fa, i );
		}
		printf( "%d\n", dfs(1) );
	}

}
