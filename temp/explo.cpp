#include <cstdio>

const int N = 1e5 + 1e4;

double Max( double a, double b ) { return a > b? a: b; }

int n, k, c, m;
int type[N], x[N];
double f[N];

int main() {
	freopen( "explo.in", "r", stdin );
	freopen( "explo.out", "w", stdout );

	scanf( "%d%d%d%d", &n, &k, &c, &m );

	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &type[i], &x[i] );
	}

	for( int i = n; i >= 1; i -- ) {
		if( type[i] == 2 ) {
			f[i] = Max( f[ i + 1 ], (double)-x[i] + f[ i + 1 ] * ( 1.0 + 0.01 * c ) );
		}
		else {
			f[i] = Max( f[ i + 1 ], (double)x[i] + f[ i + 1 ] * ( 1.0 - 0.01 * k ) );
		}
	}

	printf( "%.2lf", f[1] * m );
}
