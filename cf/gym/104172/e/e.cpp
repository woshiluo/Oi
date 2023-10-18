/*
 * e.cpp 2023-09-26
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

const int N = 1e6 + 5;

struct Seg { int l1, r1, l2, r2; };
// from [l1,r1] to [l2,r2]

int a[N], nxt[N], pre[N], lst[N];
bool vis[N];

int tree[N << 2], tree_cnt[N << 2];

inline void push_up( int now, int left, int rig ) {
    if( tree_cnt[now] ) 
        tree[now] = ( rig - left + 1 );
    else if( rig - left == 0 ) 
        tree[now] = 0;
    else 
        tree[now] = tree[ now << 1 ] + tree[ now << 1 | 1 ];
}

void query_add( int from, int to, int val, int now, int left, int rig ) {
    if( from <= left && rig <= to ) {
        tree_cnt[now] += val;
        push_up( now, left, rig );
        return ;
    }
    int mid = ( left + rig ) >> 1;
    if( from <= mid )
        query_add( from, to, val, now << 1, left, mid );
    if( to > mid )
        query_add( from, to, val, now << 1 | 1, mid + 1, rig );
    push_up( now, left, rig );
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif

	cint n = read<int>();
	cint k = read<int>();
	// TODO: k == 1
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		if( lst[ a[i] ] ) {
			nxt[ lst[ a[i] ] ] = i;
			pre[i] = lst[ a[i] ];
		}
		lst[ a[i] ] = i;
	}

	std::vector<Seg> segs, add[N], del[N];
	for( int i = 1; i <= n; i ++ ) {
		if( vis[ a[i] ] ) 
			continue;
		vis[ a[i] ] = true;
		std::vector<int> list;
		list.push_back(0);
		for( int cur = i; cur; cur = nxt[cur] )
			list.push_back(cur);
		list.push_back( n + 1 );
		cint size = list.size();
		for( int j = 1; j + k < size; j ++ ) {
			segs.push_back( (Seg) { list[ j - 1 ] + 1, list[j], list[ j + k - 1 ], list[ j + k ] - 1 } );
			add[ segs.back().l1 ].push_back( segs.back() );
			del[ segs.back().r1 ].push_back( segs.back() );
		}
	}

	ll ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( auto &seg: add[i] ) 
			query_add( seg.l2, seg.r2, 1, 1, 1, n );
		ans += tree[1];
		for( auto &seg: del[i] ) 
			query_add( seg.l2, seg.r2, -1, 1, 1, n );
	}

	ll tot = ( 1LL * n * ( n - 1 ) ) >> 1LL;
	tot += n;
	printf( "%lld\n", tot - ans );
}
