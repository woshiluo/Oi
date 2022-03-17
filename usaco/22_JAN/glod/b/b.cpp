/*
 * b.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood, and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <list>
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

int ans[N];

struct SetNode { 
	int fa; bool flag; 
	std::list<int> list;

	void full( int cur ) {
		if( flag ) 
			return ;
		flag = true;
		for( auto &x: list ) {
			ans[x] = cur;
		}
	}
} set[N];

int ecnt;
struct Edge { int from, to; } e[N];
struct Opt { int op, x; };

bool flag[N], acti[N];
std::vector<Opt> ops;

int get_fa( int cur ) {
	if( set[cur].fa == cur ) 
		return cur;
	return set[cur].fa = get_fa( set[cur].fa );
}

void merge( int u, int v, int res ) {
	int fa_u = get_fa(set[u].fa), fa_v = get_fa(set[v].fa);
	if( fa_u == fa_v )
		return ;
	u = fa_u, v = fa_v;

	if( set[u].flag || set[v].flag ) {
		set[v].full(res);
		set[u].full(res);
	}
	set[v].fa = u;
	set[u].list.splice( set[u].list.end(), set[v].list );
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int n, q; 
	n = read<int>(); q = read<int>();
	memset( acti, true, sizeof(acti) );
	for( int i = 0; i < q; i ++ ) {
		char op[3]; 
		scanf( "%s", op );
		if( op[0] == 'D' ) {
			int u = read<int>();
			ops.push_back( (Opt){ 0, u } );
			acti[u] = false;
		}
		if( op[0] == 'A' ) {
			ecnt ++;
			int u, v;
			u = read<int>();  
			v = read<int>();
			e[ecnt] = (Edge) { u, v };
			ops.push_back( (Opt) { 2, 0 } );
		}
		if( op[0] == 'R' ) {
			int u = read<int>();
			flag[u] = true;
			ops.push_back( (Opt){ 1, u } );
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		set[i] = (SetNode) { i, acti[i], { i } };
		if( acti[i] ) 
			ans[i] = q;
	}
	for( int i = 1; i <= ecnt; i ++ ) {
		if( flag[i] ) 
			continue;
		merge( e[i].from, e[i].to, q );
	}

	for( int i = q - 1; i >= 0; i -- ) {
		int u = ops[i].x;
		if( ops[i].op == 0 ) {
			acti[u] = true;
			u = get_fa(u);
			if( set[u].flag == false )
				set[u].full(i);
		}
		if( ops[i].op == 1 ) {
			merge( e[u].from, e[u].to, i );
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		printf( "%d\n", ans[i] );
	}
}
