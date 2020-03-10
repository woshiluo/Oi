#include <cstdio>
#include <cstring>

const int N = 1e5 + 1e4;

int T;
int n, m;
int a[N], b[N];

namespace subtask_n_2 {/*{{{*/
	void calc() {
		bool type_1, type_2;
		type_1 = type_2 = false;
		for( int i = 1; i <= m; i ++ ) {
			int u, v, type;
			scanf( "%d%d%d", &type, &u, &v );
			if( type == 1 ) 
				type_1 = true;
			if( type == 2 ) 
				type_2 = true;
		}
		if( type_2 ) {
			if( type_1 ) {
				printf( "YES\n" );
				return;
			}
			else {
				int sum_a = 0, sum_b = 0;
				for( int i = 1; i <= n; i ++ ) {
					sum_a += a[i], sum_b += b[i];
				}
				if( sum_a == sum_b ) {
					printf( "YES\n" );
					return;
				}
			}
		}
		else if( type_1 ) {
			if( a[2] - a[1] == b[2] - b[1] ) {
				printf( "YES\n" );
				return;
			}
		}

		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] != b[i] ) {
				flag = false;
				break;
			}
		}
		if( flag ) 
			printf( "YES\n" );
		else 
			printf( "NO\n" );
	}
}/*}}}*/

namespace subtask_t_2 {
	struct edge {
		int to, next;
	} e[ N <<  1 ];
	int ehead[N], ecnt;
	void add_edge( int now, int to ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[now];
		ehead[now] = ecnt;
	}

	int head, tail;
	int has[N], vis[N], q[N];
	void dfs( int cur, int la ) {
		vis[cur] = true;
		tail ++;
		q[tail] = cur;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			if( e[i].to == la ) 
				continue;
			if( vis[ e[i].to ] ) 
				continue;
			dfs( e[i].to, cur );
		}
	}
	void calc() {
		// Init
		memset( vis, 0, sizeof(vis) );
		memset( has, 0, sizeof(has) );
		memset( ehead, 0, sizeof(ehead) );
		ecnt = 0;
		
		for( int i = 1; i <= m; i ++ ){
			int type, u, v;
			scanf( "%d%d%d", &type, &u ,&v );
			if( type == 1 ) {
				printf( "YES\n" );
				return ;
			}
			if( u == v ) 
				continue;
			has[u] = has[v] = true;
			add_edge( u, v ), add_edge( v, u );
		}
		for( int i = 1; i <= n; i ++ ) {
			if( has[i] && vis[i] == false ) {
				head = 0, tail = -1;
				dfs( i, 0 );
				long long sum_a = 0, sum_b = 0;
				while( head <= tail ) {
					int cur = q[head];
					sum_a += a[cur], sum_b += b[cur];
					head ++;
				}
				if( sum_a != sum_b ) {
					printf( "NO\n" );
					return ;
				}
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			if( has[i] == false ) {
				if( a[i] != b[i] ) {
					printf( "NO\n" );
					return ;
				}
			}
		}
		printf( "YES\n" );
		return ;
	}
}

int main() {
	freopen( "sequence.in", "r", stdin );
	freopen( "sequence.out", "w", stdout );

	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
		}
		if( n == 2 ) 
			subtask_n_2::calc();
		else 
			subtask_t_2::calc();
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
