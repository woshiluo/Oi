// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/27 23:32:07 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 5e5 + 1e4;

int n, idx = 0;
int ans[N], val[N];
char str[N];

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

int size[N], mson[N], dep[N];

void dfs1( int cur, int la ) {
	size[cur] = 1; dep[cur] = dep[la] + 1;
	if( cur != 1 )
		val[cur] = val[la] ^ ( 1 << ( str[cur] - 'a' ) );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		dfs1( to, cur );
		size[cur] += size[to];
		if( size[ mson[cur] ] < size[to] )
			mson[cur] = to;
	}
}

int dfn[N], re_dfn[N];
void dfs2( int cur, int la, int fa, int chk[], bool valid ) {
	int cur_val = val[cur];
	if( valid ) {
		idx ++;
		dfn[cur] = idx; re_dfn[idx] = cur;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			int to = e[i].to;
			if( to == la || to == mson[cur] ) 
				continue;
			dfs2( to, cur, to, chk, true );
			for( int j = dfn[to]; j <= dfn[to] + size[to] - 1; j ++ ) {
				chk[ val[ re_dfn[j] ] ] = 0;
			}
		}
	}

	if( mson[cur] ) {
		int to = mson[cur];
		dfs2( to, cur, valid? to: fa, chk, valid );
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la || to == mson[cur] ) 
			continue;
		dfs2( to, cur, fa, chk, false );
		if( valid ) {
			for( int j = dfn[to]; j <= dfn[to] + size[to] - 1; j ++ ) {
				chk_Max( chk[ val[ re_dfn[j] ] ], dep[ re_dfn[j] ] );
			}
		}
	}

	for( int i = -1; i <= 'v' - 'a'; i ++ ) {
		int tmp = 0; 
		if( i == -1 ) 
			tmp = ( 0 ^ cur_val );
		else
			tmp = ( 0 ^ ( cur_val ^ ( 1 << i ) ) );
		int bro = chk[tmp];
		if( bro != 0 ) {
			chk_Max( ans[fa], dep[cur] + bro - 2 * dep[fa] );
		}
	}

	if( fa == cur ) 
		chk_Max( chk[cur_val], dep[cur] );
}

void push_up( int cur, int la ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		int to = e[i].to;
		if( to == la ) 
			continue;
		push_up( to, cur );
		chk_Max( ans[cur], ans[to] );
	}
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 2; i <= n; i ++ ) {
		int fa;
		char rd[3];
		scanf( "%d%s", &fa, rd );
		add_edge( fa, i );
		str[i] = rd[0];
	}

	dfs1( 1, 0 );

	{ 
		int chk[ 1 << 24 ];
		memset( chk, 0, sizeof(chk) );
		dfs2( 1, 0, 1, chk, true );
	}

	push_up( 1, 0 );

	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", ans[i] );
	}
	printf( "\n" );
}
