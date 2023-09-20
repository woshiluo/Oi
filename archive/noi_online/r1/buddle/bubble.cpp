#include <cstdio>

#include <algorithm>

const int N = 2e5 + 1e4;

int n, m;
int a[N], b[N];

int main() {
	freopen( "bubble.in", "r", stdin );
	freopen( "bubble.out", "w", stdout );

	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= m; i ++ ) {
		int type, c;
		scanf( "%d%d", &type, &c );
		if( type == 1 ) {
			std::swap( a[c], a[ c + 1 ] );
		}
		else {
			for( int i = 1; i <= n; i ++ ) {
				b[i] = a[i];
			}
			for( int i = 1; i <= c; i ++ ) {
				for( int j = 1; j < n; j ++ ) {
					if( b[j] > b[ j + 1 ] ) 
						std::swap( b[j], b[ j + 1 ] );
				}
			}
			int cnt = 0;
			for( int i = 1; i <= n; i ++ ) {
				for( int j = 1; j < n; j ++ ) { 
					if( b[j] > b[ j + 1 ] ) {
						cnt ++;
						std::swap( b[j], b[ j + 1 ] );
					}
				}
			}
			printf( "%d\n", cnt );
		}
	}
}
