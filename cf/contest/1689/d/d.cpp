/*
 * d.cpp
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

#include <map>
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

const int N = 1100;


struct SegmentTree {/*{{{*/
	int n;
	struct Node {
		int max, lazy;
	} tree[ N << 2 ];

	void push_up( cint cur ) { tree[cur].max = Max( tree[ cur << 1 ].max, tree[ cur << 1 | 1 ].max ); }
	void push_down( cint cur ) {
		if( tree[cur].lazy ) {
			int &lazy = tree[cur].lazy;
			tree[ cur << 1 ].max += lazy;
			tree[ cur << 1 | 1 ].max += lazy;
			tree[ cur << 1 ].lazy += lazy;
			tree[ cur << 1 | 1 ].lazy += lazy;
			lazy = 0;
		}
	}

	void build( cint cur, cint left, cint rig ) {
		tree[cur] = { 0, 0 };
		if( left == rig ) 
			return ;

		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void init( cint _n ) { n = _n; build( 1, 1, n ); }

	void add( cint from, cint to, cint val, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].max += val;
			tree[cur].lazy += val;
			return ;
		}

		push_down(cur);
		cint mid = ( left + rig ) >> 1;
		if( from <= mid )
			add( from, to, val, cur << 1, left, mid );
		if( to > mid )
			add( from, to, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void add( cint from, cint to, cint val ) { 
		if( to < from ) 
			return ;
		add( from, to, val, 1, 1, n );
	}

	int max() { return tree[1].max; }
} sgt;/*}}}*/

int aabs( cint cur ) { return cur < 0? -cur: cur; }
int dis( cint x1, cint y1, cint x2, cint y2 ) { return aabs( x1 - x2 ) + aabs( y1 - y2 ); }

void trans( int &n, int &m, int a[N][N] ) {
	static int b[N][N];
	for( int i = 1; i <= n; i ++ ) 
		for( int j = 1; j <= m; j ++ ) 
			b[i][j] = a[i][j];
	for( int i = 1; i <= m; i ++ ) 
		for( int j = 1; j <= n; j ++ ) 
			a[i][j] = b[j][i];

	std::swap( n, m );
}

int a[N][N], max[N];

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		int m = read<int>();


		for( int i = 1; i <= n; i ++ ) {
			static char str[N];
			scanf( "%s", str + 1 );
			for( int j = 1; j <= m; j ++ ) {
				a[i][j] = ( str[j] == 'B' );
			}
		}

		bool changed = false; 

		if( n < m ) {
			changed = true;
			trans( n, m, a );
		}

		static std::vector<int> list[N];
		for( int i = 1; i <= m; i ++ )
			list[i].clear();
		for( int i = 1; i <= n; i ++ ) 
			max[i] = 0;
		for( int i = 1; i <= n; i ++ ) 
			for( int j = 1; j <= m; j ++ ) {
				if( a[i][j] ) {
					while( list[j].size() >= 2 ) 
						list[j].pop_back();
					list[j].push_back(i);
				}
			}


		std::vector<int> ids;
		std::vector<std::pair<int, int>> nodes;
		std::map<std::pair<int, int>, int> mp;

		for( int j = 1; j <= m; j ++ ) {
			for( auto &x: list[j] ) 
				nodes.push_back( std::make_pair( x, j ) );
		}
		std::sort( nodes.begin(), nodes.end() );

		int tot = 0;
		for( auto &x: nodes ) {
			tot ++;
			chk_Max( max[ x.first ], tot );
		}
		for( int i = 1; i <= n; i ++ ) 
			chk_Max( max[i], max[ i - 1 ] );

		int cur_min = ( n + m ) * 4, cx = 0, cy = 0;
		for( int j = 1; j <= m; j ++ ) {
			sgt.init(tot);

			int cur = 0;
			for( auto &node: nodes ) {
				cur ++;
				sgt.add( cur, cur, dis( 1, j, node.first, node.second ) );
			}

			for( int i = 1; i <= n; i ++ ) {
				if( sgt.max() < cur_min ) {
					cx = i; cy = j;
					cur_min = sgt.max();
				}
				sgt.add( 1, max[i], 1 );
				sgt.add( max[i] + 1, tot, -1 );
			}
		}
		
		if( changed ) 
			printf( "%d %d\n", cy, cx );
		else
			printf( "%d %d\n", cx, cy );
	}
}
