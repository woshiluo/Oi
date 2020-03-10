#include <cstdio>

int T;
int n, m;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &m );
		printf( "%s\n", ( n % m == 0 )? "YES": "NO" );
	}
}
