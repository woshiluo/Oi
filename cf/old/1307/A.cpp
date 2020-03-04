#include <cstdio>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 110;

int T, n, d;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "A.in", "r", stdin );
	freopen( "A.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &d );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( i != 1 && a[i] != 0 ) {
				int tmp = Min( d, a[i] * ( i - 1 ) );
				tmp -= ( tmp % ( i - 1 ) );
				d -= tmp;
				a[1] += tmp / ( i - 1 );
			}
		}
		printf( "%d\n", a[1] );
	}
}
