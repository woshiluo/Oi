// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/21 22:46:20 
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

int T;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		int x1, y1, z1, x2, y2, z2;
		scanf( "%d%d%d", &x1, &y1, &z1 );
		scanf( "%d%d%d", &x2, &y2, &z2 );
		int res = 0;
		while( z1 != 0 ) {
			if( y2 != 0 ) {
				int min = Min( y2, z1 );
				y2 -= min; z1 -= min;
				res += 2 * min;
				continue;
			}
			if( z2 != 0 ) {
				int min = Min( z2, z1 );
				z1 -= min; z2 -= min;
				continue;
			}
			if( x2 != 0 ) {
				int min = Min( x2, z1 );
				x2 -= min; z1 -= min;
				continue;
			}
		}
		while( y1 != 0 ) {
			if( x2 != 0 ) {
				int min = Min( y1, x2 );
				x2 -= min; y1 -= min;
				continue;
			}
			if( y2 != 0 ) {
				int min = Min( y1, y2 );
				y1 -= min; y2 -= min;
				continue;
			}
			if( z2 != 0 ) {
				int min = Min( y1, z2 );
				y1 -= min; z2 -= min;
				res -= 2 * min;
				continue;
			}
		}
		printf( "%d\n", res );
	}
}
