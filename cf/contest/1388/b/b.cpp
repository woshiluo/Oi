// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/30 22:54:27 
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
int n;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int tmp = ( n % 4 != 0 ) + n / 4;
		for( int i = 1; i <= n - tmp; i ++ ) 
			printf( "9" );
		for( int i = 1; i <= tmp; i ++ ) 
			printf( "8" );
		printf( "\n" );
	}
}
