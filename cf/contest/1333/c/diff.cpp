// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-08 23:50
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

int main() {
	//freopen( "diff.in", "r", stdin );
	//freopen( "diff.out", "w", stdout );
	int cnt = 1;
	while(1) {
		system( "./gen.run" );
		system( "./c.run <gen.out >c.out" );
		system( "./bf.run <gen.out >bf.out" );
		printf( "%5d: ", cnt ++ );
		if( system( "diff bf.out c.out" ) != 0 ) {
			printf( "0\n" );
			return 0;
		}
		printf( "1\n" );
	}
}
