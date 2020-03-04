#include <cstdio>

inline int Max( int a, int b ) { return a > b? a: b; }

int T;
int a, b, x, y;

int main() {
#ifdef woshiluo
	freopen( "A.in", "r", stdin );
	freopen( "A.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d%d", &a, &b, &x, &y );
		x ++; y ++;
		int ans = Max( Max( ( x - 1 ) * b , ( y - 1 ) * a ), Max( ( a - x ) * b, ( b - y ) * a ) ); 
		printf( "%d\n", ans );
	}
}
