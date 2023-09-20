/*
 * legacy.cpp
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

struct Op { int id, x, y, z; };
struct Change { int fu, fv; };
std::vector<Op> ops;
std::vector<Change> changes;

int cur_time;
int fa[N], size[N], res[N];

int get_fa( cint cur ) {/*{{{*/
	if( cur == fa[cur] ) 
		return cur;
	return get_fa( fa[cur] );
} /*}}}*/

void to_time( cint gol ) {/*{{{*/
	while( cur_time < gol ) {
		cur_time ++;
		
		cint fu = changes[ cur_time ].fu;
		cint fv = changes[ cur_time ].fv;

		if( fu == fv ) 
			continue;

		fa[fv] = fu;
		size[fu] += size[fv];
	}

	while( cur_time > gol ) {
		cint fu = changes[ cur_time ].fu;
		cint fv = changes[ cur_time ].fv;
		cur_time --;

		if( fu == fv ) 
			continue;

		fa[fv] = fv;
		size[fu] -= size[fv];
	}
}/*}}}*/

void work( cint left, cint rig, std::vector<Op> &list ) {
	cint mid = ( left + rig ) >> 1;
	to_time(mid);

	std::vector<Op> lops, rops;
	for( auto &op: list ) {
		cint x = op.x;
		cint y = op.y;
		cint z = op.z;
		int tot = 0; 
		tot = size[ get_fa(x) ] + size[ get_fa(y) ];
		if( get_fa(x) == get_fa(y) ) 
			tot = size[ get_fa(x) ];

		if( tot >= z ) {
			lops.push_back(op);
			res[ op.id ] = mid;
		}
		else 
			rops.push_back(op);
	}

	if( left != rig ) {
		work( left, mid, lops );
		work( mid + 1, rig, rops );
	}
}

int main() {
	freopen( "legacy.in", "r", stdin );
	freopen( "legacy.out", "w", stdout );

	cint n = read<int>();
	cint m = read<int>();

	cur_time = m;
	changes.push_back( { 0, 0 } );
	for( int i = 1; i <= n; i ++ ) { 
		size[i] = 1;
		fa[i] = i; 
	}
	for( int i = 1; i <= m; i ++ ) {
		int u = read<int>();
		int v = read<int>();
		if( size[ get_fa(u) ] < size[ get_fa(v) ] ) 
			std::swap( u, v );

		cint fu = get_fa(u);
		cint fv = get_fa(v);

		if( fu == fv ) {
			changes.push_back( { 0, 0 } );
			continue;
		}

		changes.push_back( (Change) { fu, fv } );

		fa[fv] = fu;
		size[fu] += size[fv];
	}

	cint q = read<int>();
	for( int i = 1; i <= q; i ++ ) {
		cint x = read<int>();
		cint y = read<int>();
		cint z = read<int>();
		res[i] = m;
		ops.push_back( (Op){ i, x, y, z } );
	}

	work( 0, m, ops );

	for( int i = 1; i <= q; i ++ ) 
		printf( "%d\n", res[i] );
}
