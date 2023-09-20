#include <cstdio>

int k;
int n, a, b, c;

int main() {
	freopen( "casting.in", "r", stdin );
	freopen( "casting.out", "w", stdout );

	scanf( "%d", &k );
	scanf( "%d%d%d%d", &n, &a, &b, &c );
	if( k == 1 ) {
		int fir = ( ( a + b ) - n );
		if( fir < 0 ) 
			fir = 0;
		int sec = ( ( fir + c ) - n );
		if( sec < 0 ) 
			sec = 0;
		printf( "%d\n", sec );
	}
	else if( k == 2 ) {
		if( a > b ) 
			a = b;
		if( a > c ) 
			a = c;
		printf( "%d\n", a );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
