// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/30 22:39:29 
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
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		if( n == 36 ) 
			printf( "YES\n%d %d %d %d\n", 5, 6, 10, 15 );
		else if( n == 44 ) 
			printf( "YES\n%d %d %d %d\n", 6, 7, 10, 21 );
		else if( n == 40 ) 
			printf( "YES\n%d %d %d %d\n", 2, 6, 10, 22 );
		else if( n > 30 ) 
			printf( "YES\n%d %d %d %d\n", 6, 10, 14, n - 30 );
		else 
			printf( "NO\n" );
	}
}
