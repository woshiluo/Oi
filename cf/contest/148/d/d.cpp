// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/21 23:10:29 
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

const int N = 1100;

double f[N][N];
// w / b

double get_p( double a, double b ) {
	return a / b;
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int w, b;
	scanf( "%d%d", &w, &b );
	for( int i = 1; i <= w; i ++ ) {
		f[i][0] = 1;
	}
	for( int i = 1; i <= b; i ++ ) {
		f[0][i] = 0;
	}

	for( int i = 1; i <= w; i ++ ) {
		for( int j = 1; j <= b; j ++ ) {
			f[i][j] += get_p( i, i + j );
			if( j >= 3 ) 
				f[i][j] += get_p( j, i + j ) * get_p( j - 1, i + j - 1 ) * get_p( j - 2, i + j - 2 ) * f[i][ j - 3 ];
			if( i >= 1 && j >= 2 ) 
				f[i][j] += get_p( j, i + j ) * get_p( j - 1, i + j - 1 ) * get_p( i, i + j - 2 ) * f[ i - 1 ][ j - 2 ];
		}
	}

	printf( "%.9lf\n", f[w][b] );
}
