/*
 * byteland.cpp
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

const int N = 210;
const int INF = 0x3f3f3f3f;

struct Edge {/*{{{*/
	int to, val, next;
} e[ N << 2 ];
int ehead[N], ecnt = 1;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}/*}}}*/

bool stock[N];

int col_cnt;
int col[N], cidx[N];
namespace color {/*{{{*/
	bool vis[N];

	void dfs( int cur, int ccol ) {
		if( vis[cur] ) 
			return ;
		col[cur] = ccol; vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			dfs( e[i].to, ccol );
		}
	}

	void work( int n ) {
		for( int i = 1; i <= n; i ++ ) {
			if( !vis[i] ) {
				col_cnt ++;
				cidx[ col_cnt ] = i;
				dfs( i, col_cnt );
			}
		}
	}
}/*}}}*/

namespace bridge {/*{{{*/
	bool blocked[N], vis[N];;
	void dfs( int cur ) {
		if( vis[cur] ) 
			return ;
		vis[cur] = true;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( vis[ e[i].to ] || blocked[i] )
				continue;
			dfs( e[i].to );
		}
	}
	bool check( int p, int st, int n ) {
		blocked[ p << 1 ] = blocked[ p << 1 | 1 ] = true;
		memset( vis, 0, sizeof(vis) );
		dfs(st);
		blocked[ p << 1 ] = blocked[ p << 1 | 1 ] = false;
		for( int i = 1; i <= n; i ++ ) {
			if( col[i] == col[p] && !vis[i] )
				return false;
		}
		return true;
	}
}/*}}}*/

namespace check {/*{{{*/
	int val;
	bool blocked[N];

	struct Node {
		int need, offer;
		bool update() {
			if( offer >= need ) {
				need = 0;
				return true;
			}
			return false;
		}
	};
	Node dfs( int cur, int la, int fval, int &cnt, Node &pa ) {
		Node res = (Node) { 0, -1 };
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la || blocked[i] ) 
				continue;
			dfs( e[i].to, cur, e[i].val, cnt, res );
		}

		bool flag = res.update();
		if( stock[cur] || ( !flag && res.need + fval > val ) ) {
			if( !stock[cur] )
				cnt ++;
			res = (Node) { 0, val };
			chk_Max( pa.offer, res.offer - fval );
			chk_Max( pa.need, 0 );
		}
		else {
			chk_Max( res.offer, -1 );
			chk_Max( pa.offer, res.offer - fval );
			chk_Max( pa.need, flag? 0: res.need + fval );
		}

		if( fval == 0 && ( res.need || res.offer == -1 ) ) 
			cnt ++;

		return res;
	}

	bool work( int _val, int n, int k ) {
		static int min[N];
		val = _val;
		memset( min, INF, sizeof(min) );

		for( int i = 1; i <= col_cnt; i ++ ) {
			bool flag = false;
			for( int j = 1; j <= n; j ++ ) {
				if( col[j] == i ) {
					if( bridge::check(j, cidx[i], n) ) {
						flag = true;
						blocked[ j << 1 ] = blocked[ j << 1 | 1 ] = true;
						Node res = (Node) { 0, -1 };
						int tmp = 0; dfs( cidx[i], 0, 0, tmp, res );
						chk_Min( min[i], tmp ); 
						blocked[ j << 1 ] = blocked[ j << 1 | 1 ] = false;
					}
				}
			}
			if( !flag ) {
				Node res = (Node) { 0, -1 };
				int tmp = 0; dfs( cidx[i], 0, 0, tmp, res );
				chk_Min( min[i], tmp ); 
			}
		}
		ll res = 0;
		for( int i = 1; i <= col_cnt; i ++ ) 
			res += min[i];

		return res <= k;
	}
}/*}}}*/

int main() {
	freopen( "byteland.in", "r", stdin );
	freopen( "byteland.out", "w", stdout );

	int n, k, c;
	n = read<int>(); k = read<int>(); c = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int v = read<int>();
		add_edge( i, v + 1 );
		add_edge( v + 1, i );
	}
	for( int i = 1; i <= n; i ++ ) 
		e[ i << 1 ].val = e[ i << 1 | 1 ].val = read<int>();
	for( int i = 1; i <= c; i ++ ) 
		stock[ read<int>() + 1 ] = true;

	color::work(n);
//	bridge::work(n);

	int left = 0, rig = (int)(1e8);
	int res = rig;
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( check::work( mid, n, k ) ) {
			rig = mid - 1;
			res = mid;
		}
		else 
			left = mid + 1;
	}
	
	printf( "%d\n", res );
}
