#include <cstdio>

int n;

int main() {
	scanf( "%d", &n );
	int base = n / 3;
	int less = n - ( base * 3 );
	if( less == 0 ) {
		printf( "%d %d %d\n", base - 1, base, base + 1 );
	}
	else if( less == 1 ) {
		printf( "%d %d %d\n", base - 1, base, base + 2 );
	}
	else {
		printf( "%d %d %d\n", base - 1, base + 1, base + 2 );
	}
}
