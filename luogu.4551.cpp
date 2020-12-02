#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1e5 + 1e4;

inline void chk_Max( int &a, int b ) { a = std::max( a, b ); }

int ans = 0;

// Edge Start
struct edge {
	int to, next, val;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	e[ecnt].val = val;
	ehead[cur] = ecnt;
}
// Edge End

// Trie Start 
struct Trie {
	const int rt = 0;
	int t_cnt = 0;
	int nxt[ N * 31 * 2 ][2];
	Trie() {
		t_cnt = 0;
		memset( nxt, 0, sizeof(nxt) );
	}
	void insert( int val ) {
		int pow_2 = 1 << 30;
		int cur = rt;
		while( pow_2 ) {
			bool next_pos = ( val & pow_2 );
			if( nxt[cur][next_pos] == 0 ) 
				nxt[cur][next_pos] = ++ t_cnt;
			cur = nxt[cur][next_pos];
			pow_2 >>= 1;
		}
	}
	int query( int val ) {
		int pow_2 = 1 << 30;
		int cur = rt, res = 0;
		while( pow_2 ) {
			bool gol_pos = (bool)( val & pow_2 ) ^ 1;
			if( nxt[cur][gol_pos] != 0 ) 
				res |= pow_2;
			else 
				gol_pos ^= 1;
			cur = nxt[cur][gol_pos];
			pow_2 >>= 1;
		}
		return res;
	}
} trie;
// Trie End

void dfs( int cur, int la, int val ) {
	trie.insert(val);
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur, val ^ e[i].val );
	}
}

void dfs2( int cur, int la, int val ) {
	chk_Max( ans, trie.query(val) );
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs2( e[i].to, cur, val ^ e[i].val );
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4551.in", "r", stdin );
	freopen( "luogu.4551.out", "w", stdout );
#endif
	int n;
	scanf( "%d", &n );
	for( int i = 1, u, v, w; i < n; i ++ ) {
		scanf( "%d%d%d", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}
	
	dfs( 1, 0, 0 );

	dfs2( 1, 0, 0 );

	printf( "%d\n", ans );
}
