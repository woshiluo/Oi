#include <cstdio>

int main() {
	int n = 500000;
	printf( "%d\n", n );
	for( int i = 1; i < n; i ++ ) {
		printf( "%d %c\n", i, 'a' );
	}
}
