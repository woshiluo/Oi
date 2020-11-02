// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/25 19:11:41 
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

const int N = 110;

int T;
int n;
int a[N];

int main() {
	scanf( "%d", &T );
	while( T --  ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		for( int i = n; i >= 1; i -- ) {
			if( i > ( n >> 1 ) ) 
				printf( "%d ", - a[i] );
			else
				printf( "%d ", a[i] );
		}
		printf( "\n" );
	}
}
