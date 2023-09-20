#include <cstdio>
#include <cmath>

inline double aabs( double a ) { return a < 0? -a: a; }

struct node {
	double x, y;
} x, y;

double d;

double dis( node a, node b ) {
	double x = aabs( a.x - b.x );
	double y = aabs( a.y - b.y );
	return std::sqrt( x * x + y * y );
}

int main() {
	freopen( "jump.in", "r", stdin );
	freopen( "jump.out", "w", stdout );
	scanf( "%lf%lf%lf%lf", &x.x, &x.y, &y.x, &y.y );
	scanf( "%lf", &d );

	double line_dis = dis( x, y );
	int ans = line_dis / d;
	if( ans * d != line_dis ) {
		printf( "%d\n", ans + 1 );
		ans ++;
		double dx = ( y.x - x.x ) / d;
		double dy = ( y.y - x.y ) / d;
		double less_dis = line_dis - (double)( ans - 1 ) * d;
		double left_dis = ( less_dis + ( ans > 1 ) * d ) / 2.0;
		double left_x = x.x + ( left_dis / ( ( y.x - x.x ) / ( y.y - x.y ) ) );
		double left_y = x.y + ( left_dis / ( ( y.x - x.x ) / ( y.y - x.y ) ) ) 
			* ( ( y.x - x.x ) / ( y.y - x.y ) );
		double st_dis = std::sqrt( d * d - left_dis * left_dis );
		double st_x = left_x - ( st_dis / ( ( y.x - x.x ) / ( y.y - x.y ) ) );
		double st_y = left_y - ( ( st_dis / ( ( y.x - x.x ) / ( y.y - x.y ) ) ) 
			* ( ( y.x - x.x ) / ( y.y - x.y ) ) );
		printf( "%.9lf %.9lf", st_x, st_y );
		for( int i = 2; i <= ans; i ++ ) {
			st_x += dx, st_y += dy;
			printf( "%.9lf %.9lf", st_x, st_y );
		}
	}
	else {
		printf( "%d\n", ans );
		double dx = ( y.x - x.x ) / d;
		double dy = ( y.y - x.y ) / d;
		for( int i = 1; i <= ans; i ++ ) {
			x.x += dx, x.y += dy;
			printf( "%.9lf %.9lf", x.x, x.y );
		}
	}
}
