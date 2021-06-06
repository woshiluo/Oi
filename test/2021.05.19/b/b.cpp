#include <cstdio>
#include <cstdlib>

#include <queue>

const int N = 30;
const int MAX = 1 << 22;

int n, a;
bool vis[MAX], chk[MAX];

struct Node {
	int cur, dis;
};

void bfs( int st ) {
	std::queue<Node> q;
	q.push( (Node) { st, 0 } );
	vis[st] = true;
	while( !q.empty() ) {
		Node cur = q.front(); q.pop();
		if( chk[cur.cur] ) {
			printf( "%d\n", cur.dis );
			std::exit(0);
		}
		bool bit[N];
		for( int i = 0; i < n; i ++ ) {
			bit[i] = ( 1 & ( cur.cur >> i ) );
		}
		{
			int nxt = 0;
			for( int i = n - 1; i >= 0; i -- ) {
				nxt <<= 1;

				if( i == n - 1 )
					nxt |= bit[0];
				else
					nxt |= bit[ i + 1 ];
			}
			if( vis[nxt] == false ) {
				vis[nxt] = true;
				q.push( (Node){ nxt, cur.dis + 1 } );
			}
		}
		{
			int nxt = 0;
			for( int i = n - 1; i >= 0; i -- ) {
				nxt <<= 1;

				if( i == n - 1 )
					nxt |= bit[i];
				else if( i == n - 2 ) 
					nxt |= bit[0];
				else
					nxt |= bit[ i + 1 ];
			}
			if( vis[nxt] == false ) {
				vis[nxt] = true;
				q.push( (Node){ nxt, cur.dis + 1 } );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) { 
		int tmp;
		scanf( "%1d", &tmp );
		a = ( a << 1 ) + tmp;
	}
	{
		int tmp = 0;
		for( int i = 0; i < n; i ++ ) {
			chk[tmp] = true;
			tmp <<= 1;
			tmp |= 1;
		}
	}
	bfs(a);
}
