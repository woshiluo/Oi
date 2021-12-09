/*
 * luogu.2619.cpp
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
	for (; !isdigit(ch); ch = getchar())
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

const int N = 1e5 + 1e4;

struct Edge {
	int from, to, val;
	bool col;
};

bool cmp( const Edge &_a, const Edge &_b ) {
	if( _a.val == _b.val )
		return _a.col < _b.col;
	return _a.val < _b.val;
}

int n, m, k;
Edge edge[N];

struct CheckRes {
	int edge; ll val;
	CheckRes() { edge = 0; val = 0; }
};

struct Set {
	int set[N];
	Set( int cur ) {
		for( int i = 0; i <= cur; i ++ ) 
			set[i] = i;
	}
	int get_fa( int cur ) {
		if( cur == set[cur] ) 
			return cur;
		return set[cur] = get_fa( set[cur] );
	}

	int& operator[] ( int cur ) { return set[ get_fa(cur) ]; }
};

CheckRes check( int cur ) {
	CheckRes res;
	Set set(n);
	for( int i = 1; i <= m; i ++ ) {
		if( edge[i].col == 0 )
			edge[i].val += cur;
	}

	std::sort( edge + 1, edge + m + 1, cmp );
	for( int i = 1; i <= m; i ++ ) {
		int from = edge[i].from, to = edge[i].to;
		if( set[from] == set[to] ) 
			continue;
		set[from] = set[to];
		res.val += edge[i].val;
		res.edge += ( edge[i].col == 0 );
	}
	for( int i = 1; i <= m; i ++ ) {
		if( edge[i].col == 0 )
			edge[i].val -= cur;
	}
	return res;
}

int get_ans( int cur ) {
	int res = 0;
	Set set(n);
	for( int i = 1; i <= m; i ++ ) {
		if( edge[i].col == 0 )
			edge[i].val += cur;
		edge[i].col ^= 1;
	}

	int whith_cnt = k;
	std::sort( edge + 1, edge + m + 1, cmp );
	for( int i = 1; i <= m; i ++ ) {
		int from = edge[i].from, to = edge[i].to;
		if( set[from] == set[to] ) 
			continue;
		if( edge[i].col && whith_cnt <= 0 ) 
			continue;
		set[from] = set[to];
		res += edge[i].val;
		whith_cnt -= edge[i].col;
	}
	return res - cur * k;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2619.in", "r", stdin );
	freopen( "luogu.2619.out", "w", stdout );
#endif
	n = read<int>(); m = read<int>(); k = read<int>();
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w; bool col;
		u = read<int>(); v = read<int>(); w = read<int>(); col = read<int>();
		edge[i] = (Edge) { u, v, w, col };
	}

	int left = -110, rig = 110, p = -110;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		CheckRes res = check(mid);
		if( res.edge >= k ) {
			left = mid + 1;
			p = mid;
		}
		else {
			rig = mid - 1;
		}
	}

	printf( "%lld\n", check(p).val - p * k);
}
