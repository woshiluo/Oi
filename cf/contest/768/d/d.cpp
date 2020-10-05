// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/23 22:35:38 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e4 + 1e3;
const int K = 1e3 + 1e2;
const double eps = 1e-8;

int k, q;
double f[N][K];

double get_p( double a, double b ) { return a / b; }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d%d", &k, &q );
	int p1 = 1;
	f[0][0] = 1;
	while( 1 ) {
		for( int i = 1; i <= k; i ++ ) {
			f[p1][i] += f[ p1 - 1 ][i] * get_p( 1, k ) * (double)i;
			f[p1][i] += f[ p1 - 1 ][ i - 1 ] * get_p( 1, k ) * (double)( k - i + 1 );
		}
		if( f[p1][k] + eps >= 0.5 ) {
			break;
		}
//		printf( "%d %lf\n", p1, f[p1][k] );
		p1 ++;
	}
	while( q -- ) {
		int a;
		scanf( "%d", &a );
		double gol = get_p( (double)a - eps, 2000 );
		int res = 1;
		for( res = 1; res <= p1; res ++ ) {
			if( f[res][k] >= gol ) {
				break;
			}
		}
		printf( "%d\n", res );
	}
}
