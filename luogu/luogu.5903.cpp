#include <cstdio>

#include <vector>

const int N = 5e5 + 1e3;

int n, q, rt;
int dep[N], mdep[N], mson[N], top[N], len[N], highbit[N], fa[N][20];
std::vector<int> len_fa[N], len_son[N];

// Edge Start 
struct edge {
	int to, next;
} e[N];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

namespace gen{ 
	unsigned int s;
	int x, k;
	long long last_ans, ans;
	inline unsigned int get( unsigned int x ) {
		x ^= x << 13;
		x ^= x >> 17;
		x ^= x << 5;
		return s = x; 
	}
	inline void init() {
		last_ans = 0; ans = 0;
		x = ( ( get(s) ^ last_ans ) % n ) + 1;
		k = ( get(s) ^ last_ans ) % dep[x];
	}
	inline void update_ans( int i, int cur_ans ) {
		last_ans = cur_ans;
		x = ( ( get(s) ^ last_ans ) % n ) + 1;
		k = ( get(s) ^ last_ans ) % dep[x];
		ans ^= ( 1LL * i * cur_ans );
	}
}

void dfs1( int now, int la ) {
	fa[now][0] = la;
	for( int k = 1; k <= 17; k ++ ) {
		fa[now][k] = fa[ fa[now][ k - 1 ] ][ k - 1 ];
	}
	dep[now] = dep[la] + 1;
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs1( e[i].to, now );
		if( mdep[ e[i].to ] > mdep[ mson[now] ] )
			mson[now] = e[i].to;
	}
	mdep[now] = mdep[ mson[now] ];
	if( mdep[now] == 0 )
		mdep[now] = dep[now];
}

void dfs2( int now, int la ) {
	if( top[now] == 0 ) 
		top[now] = now;
	len[ top[now] ] ++;
	if( mson[now] == 0 )
		return ;
	top[ mson[now] ] = top[now];
	dfs2( mson[now], now );
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( e[i].to == la || e[i].to == mson[now] ) 
			continue;
		dfs2( e[i].to, now );
	}
}

void init_len() {
	for( int i = 1; i <= n; i ++ ) {
		if( top[i] == i )  {
			int tmp_len = len[ top[i] ];
			int tmp_fa, tmp_son;
			tmp_fa = tmp_son = i;
			for( int o = 1; o <= tmp_len; o ++ ) {
				len_fa[i].push_back( tmp_fa );
				len_son[i].push_back( tmp_son );
				tmp_fa = fa[ tmp_fa ][0];
				tmp_son = mson[ tmp_son ];
			}
		}
	}
}

void gen_highbit() {
	int cur_p = 1, next = 2; 
	for( int i = 1; i <= n; i ++ ) {
		if( i >= next )
			next <<= 1, cur_p ++;
		highbit[i] = cur_p;
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.5903.in", "r", stdin );
	freopen( "luogu.5903.out", "w", stdout );
#endif
	scanf( "%d%d%u", &n, &q, &gen::s );
	for( int i = 1, u; i <= n; i ++ ) {
		scanf( "%d", &u );
		if( u == 0 ) 
			rt = i;
		else 
			add_edge( u, i );
	}

	dfs1( rt, 0 );
	dfs2( rt, 0 );

	init_len();
	gen_highbit();

	gen::init();
	for( int i = 1; i <= q; i ++ ) {
		int x = gen::x, k = gen:: k;
		if( k == 0 ) {
			gen::update_ans( i, x );
			continue;
		}
		int cur = fa[x][ highbit[k] - 1 ];
		cur = top[cur];
		int wantd_dep = dep[x] - k;
		if( dep[cur] == wantd_dep )
			gen::update_ans( i, cur );
		else if( dep[cur] > wantd_dep ) {
			int tmp = dep[cur] - wantd_dep;
			gen::update_ans( i, len_fa[cur][tmp] );
		}
		else {
			int tmp = wantd_dep - dep[cur];
			gen::update_ans( i, len_son[cur][tmp] );
		}
	}

	printf( "%lld\n", gen::ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
