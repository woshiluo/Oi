// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020/04/08 22:39:10
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

int T;
int n, m;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &m );
		for( int i = 1; i < n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				printf( "B" );
			}
			printf( "\n" );
		}
		for( int j = 1; j < m; j ++ ) 
			printf( "B" );
		printf( "W" );
		printf( "\n" );
	}
}
