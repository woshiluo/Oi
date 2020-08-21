#include <cstdio>

int T;
int n;

bool is_in( int a, int b, int c)  {
	return b <= a && a <= c;
}

double calc( int scr ) {
	if( is_in( scr, 95,100 ) ) return 4.3;
	if( is_in( scr, 90,94 ) )  return 4.0;
	if( is_in( scr, 85,89 ) )  return 3.7;
	if( is_in( scr, 80,84 ) )  return 3.3;
	if( is_in( scr, 75,79 ) )  return 3.0;
	if( is_in( scr, 70,74 ) )  return 2.7;
	if( is_in( scr, 67,69 ) )  return 2.3;
	if( is_in( scr, 65,66 ) )  return 2.0;
	if( is_in( scr, 62,64 ) )  return 1.7;
	if( is_in( scr, 60,61 ) )  return 1.0;
	if( is_in( scr, 0,59  ) )  return 0;
	return 0;
}

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		double ans = 0;
		for( int p1 = 60; p1 <= 100; p1 ++ ) {
			if( p1 > n )
				break;
			for( int p2 = 60; p2 <= 100; p2 ++ ) {
				if( p1 + p2 > n ) {
					double res = calc( p1 );
					if( res > ans ) 
						ans = res;
					break;
				}
				for( int p3 = 60; p3 <= 100; p3 ++ ) {
					if( p1 + p2 + p3 > n ) {
						double res = calc( p1 ) + calc( p2 );
						if( res > ans ) 
							ans = res;
						break;
					}
					for( int p4 = 60; p4 <= 100; p4 ++ ) {
						if( p1 + p2 + p3 + p4 > n ) {
							double res = calc( p1 ) + calc( p2 ) + calc( p3 );
							if( res > ans ) 
								ans = res;
							break;
						}
						if( p1 + p2 + p3 + p4 != n ) 
							continue;
						double res = calc( p1 ) + calc( p2 ) + calc( p3 ) + calc( p4 );
						if( res > ans ) 
							ans = res;
					}
				}
			}
		}
		printf( "%.1lf\n", ans );
	}
}
