/*
 * tree.cpp
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

const int N = 5e5 + 1e4;
const int INF = 0x3f3f3f3f;

// Edge Start
struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

int rt;
int f[N][2], degree[N];
void dfs( int cur, int la, int &res ) {
	int size = 0, sum1 = 0, sum0 = 0;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;

		dfs( to, cur, res );

		size ++;
		sum1 += f[to][1];
		sum0 += f[to][0];
	}
	if( size == 0 ) {
		f[cur][1] = 1;
		f[cur][0] = 0;
		return ;
	}

	int sum = sum1 + sum0;
	if( cur == rt ) {
		res += sum / 2;
		if( ( sum & 1 ) && sum1 == 0 ) 
			res ++;
		return ;
	}
	if( sum & 1 ) {
		res += ( sum - 1 ) / 2;
		if( sum1 )
			f[cur][1] = 1;
		else if( sum0 )
			f[cur][0] = 1;
	}
	else {
		if( sum1 == 0 ) {
			res += sum / 2;
			f[cur][1] = f[cur][0] = 0;
		}
		else {
			res += ( sum - 1 ) / 2;
			f[cur][1] = 0; f[cur][0] = 1;
		}
	}
}

int n;

int main() {
#ifdef woshiluo
	freopen( "tree.in", "r", stdin );
	freopen( "tree.out", "w", stdout );
#endif
	n = read<int>();
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		u = read<int>(); v = read<int>();
		degree[u] ++; degree[v] ++;
		add_edge( u, v );
		add_edge( v, u );
	}

	for( int i = 1; i <= n; i ++ ) {
		if( degree[i] != 1 ) {
			rt = i;
			break;
		}
	}

	int res = 0;
	dfs( rt, 0, res );

	printf( "%d\n", res );
}
