// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/25 12:34:45 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e5 + 1e4;

// Edge Start 
struct edge {
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

int n;
int col[N];
long long ans[N];

int son[N], mson[N];
void dfs1( int cur, int la ) { 
	son[cur] = 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la )
			continue;
		dfs1( to, cur );
		son[cur] += son[to];
		if( son[ mson[cur] ] < son[to] )
			mson[cur] = to;
	}
}

void dfs2( int cur, int la, std::map<int, int> &sum, long long &res, int &max_cnt, bool valid ) {
	int cur_col = col[cur];

	if( valid ) {
		for( int i = ehead[cur]; i; i = e[i].next ) {
			int to = e[i].to;
			if( to == la || to == mson[cur] ) 
				continue;
			long long tmp_res = 0; int tmp_cnt = 0;
			std::map<int, int> mp;
			dfs2( to, cur, mp, tmp_res, tmp_cnt, valid && true );
		}
	}

	if( mson[cur] ) {
		dfs2( mson[cur], cur, sum, res, max_cnt, valid && true );
	}

	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la || to == mson[cur] )
			continue;
		dfs2( to, cur, sum, res, max_cnt, false );
	}

	sum[cur_col] ++;
	if( sum[cur_col] > max_cnt ) {
		max_cnt = sum[cur_col];
		res = cur_col;
	}
	else if( sum[cur_col] == max_cnt ) {
		res += cur_col;
	}

	if( valid ) {
		ans[cur] = res;
	}
}

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &col[i] );
	}
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v );
		add_edge( v, u );
	}

	dfs1( 1, 0 );

	{
		long long tmp1 = 0; int tmp2 = 0;
		std::map<int, int> sum;
		dfs2( 1, 0, sum, tmp1, tmp2, true );
	}

	for( int i = 1; i <= n; i ++ ) {
		printf( "%lld ", ans[i] );
	}
}
