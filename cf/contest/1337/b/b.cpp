// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/15 22:48:52 
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
T chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
T chk_Min( T &a, T b ) { if( b < a ) a = b; }

int T;
int x, n, m;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &x, &n, &m );
		while( n -- ) {
			int after = x / 2 + 10;
			int less = x - after;
			if( less <= 0 )
				break;
			x = after;
		}
		printf( "%s\n", ( m * 10 >= x )? "YES": "NO" );
	}
}
