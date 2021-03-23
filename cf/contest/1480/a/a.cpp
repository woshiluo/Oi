// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/07 22:36:24 
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

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		char str[N];
		scanf( "%s", str );
		int len = strlen(str);
		for( int i = 0; i < len; i ++ ) {
			if( i & 1 ) {
				if( str[i] == 'z' )
					printf( "%c", 'y' );
				else
					printf( "%c", 'z' );
			}
			else {
				if( str[i] == 'a' )
					printf( "%c", 'b' );
				else
					printf( "%c", 'a' );
			}
		}
		printf( "\n" );
	}
}
