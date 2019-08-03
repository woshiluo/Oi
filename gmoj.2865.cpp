#include <cstdio>

#include <algorithm>

const int N = 61000;

struct node {
	int x, y, k, id;	
} a[N];

int n, m;
int b[N];
char op[20];

bool cmp( node a, node b ) { return a.k < b.k; }

int main() {
#ifdef woshiluo
	freopen( "gmoj.2865.in", "r", stdin );
	freopen( "gmoj.2865.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i++ ) {
		scanf( "%d%d%d", &a[i].x, &a[i].y, &a[i].k );
		a[i].id = i;
	}

	std::sort( a + 1, a + n + 1, cmp );

	for( int i = 1; i <= n; i++ ) 
		b[ a[i].id ] = i;

	while( m -- ) {
		scanf( "%s", op );
		if( op[0] == 'S' ) {
			int x, y;
			scanf( "%d%d", &x, &y );
			x ++, y ++;
			std::swap( a[ b[x] ].x, a[ b[y] ].x );
			std::swap( a[ b[x] ].y, a[ b[y] ].y );
			std::swap( a[ b[x] ].id, a[ b[y] ].id );
			std::swap( b[x], b[y] );
		}
		else {
			int x0, y0, x1, y1, k, cnt = 0;
			bool flag = false;
			scanf( "%d%d%d%d%d", &x0, &y0, &x1, &y1, &k );
			if( x0 > x1 )
				std::swap( x0, x1 );
			if( y0 > y1 )
				std::swap( y0, y1 );
			for( int i = 1; i <= n; i++ ) {
				if( a[i].x >= x0 && a[i].x <= x1 && a[i].y >= y0 && a[i].y <= y1 ) {
					cnt ++;
					if( cnt == k ) {
						printf( "%d", a[i].k );	
						flag = true;
						break;
					}
				}
			}	

			if( !flag ) 
				printf( "It doesn't exist." );
			printf( "\n" );
		}
	}
}
