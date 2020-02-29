#include <cstdio>

int T;
int n, g, b;

int main() {
#ifdef woshiluo
	freopen( "B.in", "r", stdin );
	freopen( "B.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &n, &g, &b );
		int n_2 = ( n / 2 ) + ( n & 1 );
		int n1 = n_2 / g, n2 = n_2 % g;
		if( n1 > 0 && n2 == 0 ) {
			n1 --, n2 = g;
		}
		long long base = 1LL * n1 * ( g + b ) + (long long)n2;
		if( base < n ) 
			base = n;
		printf( "%lld\n", base ); 
	}
}
