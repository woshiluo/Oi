#include <cstdio>

int T;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		bool flag = false;
		for( int i = 0; i <= n; i ++ ) {
			for( int j = 0; j <= n; j ++ ) {
				int cur = i * 3 + 5 * j;
				if( cur > n ) 
					continue;
				if( ( n - cur ) % 7 == 0 ) {
					if( flag ) 
						continue;
					flag = true;
					printf( "%d %d %d\n", i, j, ( n - cur ) / 7 );
				}
			}
		}
		if( flag == false ) {
			printf( "-1\n" );
		}
	}
}
