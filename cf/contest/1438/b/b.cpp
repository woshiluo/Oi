// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/13 23:06:24 
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

const int N = 1e5 + 1e4;

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, a[N];
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		bool flag = false;
		for( int i = 2; i <= n; i ++ ) {
			if( a[i] == a[ i - 1 ] ) 
				flag = true;
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
