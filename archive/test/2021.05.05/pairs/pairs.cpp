#include <cstdio>

inline int lowbit( int cur ) { return cur & ( - cur ); }

int T, n;

int main() {
	freopen( "pairs.in", "r", stdin );
	freopen( "pairs.out", "w", stdout );

	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int tmp = n ^ ( n >> 1 ), cnt = 0;
		while( tmp ) {
			tmp -= lowbit(tmp);
			cnt ++;
		}
		printf( "%d\n", ( n - cnt ) >> 1 );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
