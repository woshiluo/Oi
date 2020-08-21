// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/03 21:16:26 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

const int N = 310;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int T;
int n, k;
int a[N][N], row[N], col[N];;

inline int pow( int a ) { return a * a; }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &k );
		memset( a, 0, sizeof(a) );
		memset( row, 0, sizeof(row) );
		memset( col, 0, sizeof(col) );
		int x = 1, y = 1;
		while( k -- ) {
			a[x][y] = 1;
			row[x] ++;
			col[y] ++;
			x ++, y ++;
			if( x > n ) 
				x = 1;
			if( y > n ) 
				y = 1;
			while( a[x][y] ) 
				x ++;
		}
		std::sort( col + 1, col + 1 + n );
		std::sort( row + 1, row + 1 + n );
		printf( "%d\n", pow(col[n] - col[1]) + pow(row[n] - row[1]) );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++ ) {
				printf( "%d", a[i][j] );
			}
			printf( "\n" );
		}
	}
}
