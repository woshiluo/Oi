// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/28 22:41:17 
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

int pow( int a, int p ) {
	int res = 1;
	for( int i = 1; i <= p; i ++ )
		res = res * a;
	return res;
}

const int D = 20;
const int N = 200;

bool f[D][N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	for( int d = 1; d <= 10; d ++ ) {
		f[d][0] = true;
		for( int i = 0; i <= 100; i ++ ) {
			for( int k = 0; k <= 9; k ++ ) {
				for( int base = 0; base <= 1; base ++ ) {
					int val = k * pow( 10, base ) + d * pow( 10, base ^ 1 );
					if( i + val <= 100 ) {
						f[d][ i + val ] = ( f[d][ i + val ] || f[d][i] );
					}
				}
			}
		}
	}
	while( T -- ) {
		int q, d;
		scanf( "%d%d", &q, &d );
		for( int i = 1; i <= q; i ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			if( tmp <= 100 ) {
				printf( "%s\n", f[d][tmp]? "YES": "NO" );
			}
			else
				printf( "%s\n", "YES" );
		}
	}
}
