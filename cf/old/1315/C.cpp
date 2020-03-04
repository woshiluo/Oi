#include <cstdio>
#include <cstring>

#include <queue>

const int N = 210;

int T;
int n, b[N];
bool vis[N];

int main() {
#ifdef woshiluo
	freopen( "C.in", "r", stdin );
	freopen( "C.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		int n2;
		std::queue<int> q;
		bool flag = false;
		memset( vis, 0, sizeof( vis ) );

		scanf( "%d", &n );
		n2 = 2 * n;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &b[i] );
			vis[ b[i] ] = true;
		}
		for( int i = 1; i <= n; i ++ ) {
			q.push( b[i] );
			int tmp = b[i] + 1;
			while( tmp <= n2 && vis[tmp] == true ) 
				tmp ++;

			if( tmp == n2 + 1 ) {
				flag = true;
				break;
			}
			q.push(tmp);
			vis[tmp] = true;
		}
		if( flag ) {
			printf( "-1\n" );
			continue;
		}
		while( !q.empty() ) {
			printf( "%d ", q.front() );
			q.pop();
		}
		printf( "\n" );
	}
}
