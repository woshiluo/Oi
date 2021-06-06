#include <cstdio>

const int N = 1e5 + 1e4;

int n;
int a[N];
char str[N];

int map_int( char _a ) {
	// W 0 
	// R 1
	// B 2
	if( _a == 'W' ) 
		return 0;
	if( _a == 'R' ) 
		return 1;
	if( _a == 'B' ) 
		return 2;
	return 0;
}

char map_char( int _a ) {
	if( _a == 0 ) 
		return 'W';
	if( _a == 2 ) 
		return 'R';
	if( _a == 1 ) 
		return 'B';
	return 'W';
}

int fac( int _a ) {
	if( _a == 1 ) 
		return 1;
	if( _a == 2 ) 
		return 2;
	if( _a == 3 ) 
		return 6;

	return 1;
}

int _C( int _n, int m, int p ) { return ( fac(m) / fac( m - _n ) / fac(_n) ) % p; }

int lucas( int _n, int m, int p ) {
	if( _n == 0 || m == 0 ) 
		return 1;
	return ( lucas( _n / p, m / p, p ) * _C( _n % p, m % p, p ) ) % p;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &n );
	scanf( "%s", str );
	for( int i = 0; i < n; i ++ ) {
		a[ i + 1 ] = map_int( str[i] );
	}

	int ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		ans = ( ans + a[i] * lucas( i - 1, n - 1, 3 ) ) % 3;
	}

	printf( "%c\n", map_char( ans ) );
}
