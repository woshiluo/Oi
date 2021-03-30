#include <cstdio>

#include <algorithm>

const int N = 1100;

void reverse( int a[], int left, int rig ) {
	while( left < rig ) {
		std::swap( a[left], a[rig] );
		left ++; rig --;
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	for( int _case = 1; _case <= T; _case ++ ) {
		int n, c;
		int a[N];
		
		scanf( "%d%d", &n, &c );
		for( int i = 1; i <= n; i ++ ) 
			a[i] = i;
		c -= n - 1;

		for( int i = n - 1; i >= 1; i -- ) {
			int max = n - i;
			int nxt = std::max( 0, std::min( max, c ) );

			reverse( a, i, i + nxt );
			c -= nxt;
		}

		printf( "Case #%d: ", _case );
		if( c != 0 ) 
			printf( "IMPOSSIBLE" );
		else {
			for( int i = 1; i <= n; i ++ ) 
				printf( "%d ", a[i] );
		}
	
		printf( "\n" );
	}
}
