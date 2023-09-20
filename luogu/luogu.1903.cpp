/*
 * luogu.1903.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <algorithm>

typedef int ll;
typedef unsigned int ull;

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
/*}}}*/

const int N = 133500;
const int M = 1e6 + 5;

int cur = 0, l = 0, r = 0, blk;
int a[N], ans[N], pool[M], cnt;
struct Query { int id, l, r, t; } query[N];
struct Change { int id, pos, val; } change[N];

bool cmp( Query &_a, Query &_b ) {
	if( _a.l / blk == _b.l / blk ) {
		if( _a.r / blk == _b.r / blk ) 
			return _a.id < _b.id;
		return _a.r / blk < _b.r / blk;
	}
	return _a.l / blk < _b.l / blk;
}

inline void del( const int _cur ) {
	pool[_cur] -= 1;
	cnt -= ( pool[_cur] == 0 );
}
inline void add( const int _cur ) {
	pool[_cur] += 1;
	cnt += ( pool[_cur] == 1 );
}
inline void add_time() {
	cur ++;
	int &pos = change[cur].pos;
	if( l <= pos && pos <= r ) {
		del( a[pos] ); add( change[cur].val );
	}
	std::swap( a[pos], change[cur].val );
}
inline void del_time() {
	int &pos = change[cur].pos;
	if( l <= pos && pos <= r ) {
		del( a[pos] ); add( change[cur].val );
	}
	std::swap( a[pos], change[cur].val );
	cur --; 
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1903.in", "r", stdin );
	freopen( "luogu.1903.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	blk = std::pow( n, (double)2/(double)3 );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	int cnt_r = 0, cnt_q = 0;
	for( int i = 1; i <= m; i ++ ) {
		char op[3]; int x, y;
		scanf( "%s", op ); x = read<int>(); y = read<int>();
		if( op[0] == 'Q' ) {
			cnt_q ++;
			query[cnt_q] = ( (Query) { cnt_r, x, y, cnt_q } );
		}
		else {
			cnt_r ++;
			change[cnt_r] = ( (Change) { cnt_r, x, y } );
		}
	}

	std::sort( query + 1, query + cnt_q + 1, cmp );

	for( int i = 1; i <= cnt_q; i ++ ) {
		while( r < query[i].r ) 
			add( a[ ++ r ] );
		while( r > query[i].r ) 
			del( a[ r -- ] );
		while( l < query[i].l ) 
			del( a[ l ++ ] );
		while( l > query[i].l ) 
			add( a[ -- l ] );
		while( cur < query[i].id ) add_time();
		while( cur > query[i].id ) del_time();
		ans[ query[i].t ] = cnt;
	}

	for( int i = 1; i <= cnt_q; i ++ ) 
		printf( "%d\n", ans[i] );
}
