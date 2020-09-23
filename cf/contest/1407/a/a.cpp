// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/08 22:35:25 
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

const int N = 1e3 + 1e2;

int T;
int n;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int one = 0, zero = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( a[i] == 0 )
				zero ++;
			if( a[i] == 1 ) 
				one ++;
		}
		if( one & 1 )
			one --;
		if( one >= zero ) {
			printf( "%d\n", one );
			for( int i = 1; i <= one; i ++ ) {
				printf( "1 " );
			}
			printf( "\n" );
		}
		else {
			printf( "%d\n", zero );
			for( int i = 1; i <= zero; i ++ ) {
				printf( "0 " );
			}
			printf( "\n" );
		}
	}
}
