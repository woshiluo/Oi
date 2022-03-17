/*
 * g.cpp
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


const int N = 1e6 + 1e5;

template <class T>
T aabs( T a ) { return a > 0? a: -a; }

struct SegmentTree {
	int sum[N], res;
	SegmentTree() {
		memset( sum, 0, sizeof(sum) );
		res = 0;
	}

	void add( int pos, int val ) { 
		sum[pos] += val;
		if( val == 1 && aabs( sum[pos] % 2 ) == 0 ) 
			res ++;
		if( val == -1 && aabs( sum[pos] % 2 ) == 1 ) 
			res --;
	}

	int get_cur() { return res; }
};

struct Ask { int id; int left, rig; };

int a[N], ans[N];
std::vector<Ask> ask;

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif
	int n = read<int>();
	int blk = 2000;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	int q = read<int>();
	for( int i = 1; i <= q; i ++ ) {
		int l, r;
		l = read<int>(); r = read<int>();
		ask.push_back( (Ask) { i, l, r } );
	}
	std::sort( ask.begin(), ask.end(), [blk]( const Ask &_a, const Ask &_b ) {
		int ba = _a.left / blk;
		int bb = _b.left / blk;
		if( ba == bb ) {
			return _a.rig < _b.rig;
		}
		else
			return ba < bb;
	});

	int l = 1, r = 1;
	SegmentTree seg;
	seg.add( a[1], 1 );
	auto add_l = [&] {
		seg.add( a[l], -1 );
		l ++;
	};
	auto del_l = [&] {
		l --;
		seg.add( a[l], 1 );
	};
	auto add_r = [&] {
		r ++;
		seg.add( a[r], 1 );
	};
	auto del_r = [&] {
		seg.add( a[r], -1 );
		r --;
	};
	for( auto &qu: ask ) {
		while( l > qu.left )
			del_l();
		while( r < qu.rig )
			add_r();
		while( l < qu.left )
			add_l();
		while( r > qu.rig )
			del_r();
		ans[ qu.id ] = seg.get_cur();
	}
	for( int i = 1; i <= q; i ++ ) 
		printf( "%d\n", ans[i] );
}
