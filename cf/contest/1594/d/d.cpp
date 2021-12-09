/*
 * d.cpp
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

const int N = 2e5 + 1e4;
const int M = 5e5 + 1e4;

struct Edge {
	int to, next, val;
} e[ M << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

bool vis[N];
void init() {
	ecnt = 0;
	memset( ehead, 0, sizeof(ehead) );
	memset( vis, 0, sizeof(vis) );
}

int try_who( int cur, int who, int tag[] ) {
	int res = who;
	tag[cur] = who;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to, val = e[i].val;

		int should_value = -1;
		if( val == 0 ) 
			should_value = who? 0: 1;
		else if( val == 1 ) 
			should_value = who? 1: 0;
		else 
			should_value = ( who == ( val - 2 ) );

		if( tag[to] != -1 ) {
			if( tag[to] != should_value ) 
				return -1;
		}
		else {
			int tmp = try_who( to, should_value, tag );
			if( tmp == -1 ) 
				return -1;
			res += tmp;
		}
	}
	return res;
}

int work() {
	init();
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		int u, v;
		char str[20];
		scanf( "%d%d%s", &u, &v, str );
		add_edge( u, v, str[0] == 'c' );
		add_edge( v, u, ( str[0] == 'c' ) + 2 );
	}

	int ans = 0;
	static int tag[2][N];
	memset( tag, -1, sizeof(tag) );
	for( int i = 1; i <= n; i ++ ) {
		if( tag[0][i] == -1 ) {
			int res = -1;
			// 0 impo
			// 1 crew 
			chk_Max( res, try_who( i, 0, tag[0] ) );
			chk_Max( res, try_who( i, 1, tag[1] ) );
			if( res == -1 )
				return -1;
			ans += res;
		}
	}
	return ans;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		printf( "%d\n", work() );
	}
}
