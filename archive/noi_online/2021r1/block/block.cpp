#include <cstdio>
#include <cstring>

const int N = 3100;
const int M = N * N;

int rt = 1;
int node_cnt = 1;
struct Node {
	int cur;
} node[M];

struct edge {
	int to, next;
} e[M];
int ehead[M], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int n;
char a[N], b[N];
int a_next[N][26];

int chk( int cur, int nxt ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( node[ e[i].to ].cur == nxt ) 
			return e[i].to;
	}
	return 0;
}

int search( int pos ) {
	int cur = rt, a_pos = 0, res = 0;
	for( ; pos <= n; pos ++ ) {
		int nxt = chk( cur, b[pos] );
		int a_nxt = a_next[a_pos][ b[pos] ];

		if( a_nxt == -1 ) 
			return res;
		else 
			a_pos = a_nxt;

		if( nxt ) 
			cur = nxt;
		else {
			res ++;
			node_cnt ++;
			node[node_cnt] = (Node){ b[pos] };
			add_edge( cur, node_cnt );
			cur = node_cnt;
		}
	}
	return res;
}

int main() {
//	freopen( "block.in", "r", stdin );
//	freopen( "block.out", "w", stdout );

	scanf( "%d", &n );
	scanf( "%s%s", a + 1, b + 1 );
	for( int i = 1; i <= n; i ++ ) { a[i] -= 'a'; b[i] -= 'a'; }
	{
		int cur[32];
		memset( cur, -1, sizeof(cur) );
		for( int i = n; i >= 0; i --  ) {
			for( int j = 0; j < 26; j ++ ) {
				a_next[i][j] = cur[j];
			}
			cur[ a[i] ] = i;
		}
	}

	int ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		ans += search(i);
	}
	printf( "%d\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
