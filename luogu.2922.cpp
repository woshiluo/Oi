#include <cstdio>

const int N = 5e5 + 1e4;

int m, n;

struct Trie {
	const static int rt = 0;
	int t_cnt = 0;
	int cnt[ N << 2 ], sum[ N << 2 ];
	int next[ N << 2 ][2];
	void insert( int *p, int n ) {
		int cur = rt;
		for( int i = 1; i <= n; i ++, p ++ ) {
			if( next[cur][*p] == 0 ) 
				next[cur][*p] = ++ t_cnt;
			cur = next[cur][*p];
		}
		cnt[cur] ++;
	}
	void build( int cur = rt ) {
		sum[cur] += cnt[cur];
		if( next[cur][0] ) {
			build( next[cur][0] );
			sum[cur] += sum[ next[cur][0] ];
		}
		if( next[cur][1] ) {
			build( next[cur][1] );
			sum[cur] += sum[ next[cur][1] ];
		}
	}
	int query( int *p, int n ) {
		int cur = rt;
		int res = 0;
		for( int i = 1; i <= n; i ++, p ++ ) {
			if( next[cur][*p] == 0 ) 
				next[cur][*p] = ++ t_cnt;
			res += cnt[cur];
			cur = next[cur][*p];
		}
		res += sum[cur];
		return res;
	}
} trie;


int main() {
#ifdef woshiluo
	freopen( "luogu.2922.in", "r", stdin );
	freopen( "luogu.2922.out", "w", stdout );
#endif
	scanf( "%d%d", &m, &n );
	for( int i = 1; i <= m; i ++ ) {
		int pos;
		scanf( "%d", &pos );
		int *npt = new int[ pos + 10 ];
		for( int j = 1; j <= pos; j ++ ) {
			scanf( "%d", npt + j );
		}
		trie.insert( npt + 1, pos );
		delete [] npt;
	}

	trie.build();
	
	for( int i = 1; i <= n; i ++ ) {
		int pos;
		scanf( "%d", &pos );
		int *npt = new int[ pos + 10 ];
		for( int j = 1; j <= pos; j ++ ) {
			scanf( "%d", npt + j );
		}
		printf( "%d\n", trie.query( npt + 1, pos ) );
		delete [] npt;
	}
}
