#include <cstdio>

const int N = 1e5 + 1e4;

int n, m;
int t;
int a[N];

void dfs( int cur, int dep ) {
}

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		int sum;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= m; i ++ ) {
			scanf( "%d", &a[i] );
			sum += a[i];
		}
		if( sum < n ) {
			printf( "-1\n" );
			continue;
		}			
		dfs( n );
	}
}
