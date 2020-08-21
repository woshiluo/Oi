#include <cstdio>

const int N = 1e5 + 1e4;

int T;
int n, m;
int x[N], y[N];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &m );
		int min_cal = (int)(1e9 + 1e8);
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d%d", &x[i], &y[i] );
			int res = ( ( m / x[i] ) + ( m % x[i] != 0 ) ) * y[i];
			if( res < min_cal )
				min_cal = res;
		}
		printf( "%d\n", min_cal );
	}
}
