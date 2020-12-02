// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/02 22:39:55 
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


int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		int cnt = 4 * n;
		while( n ) {
			printf( "%d ", cnt );
			cnt -= 2;
			n --;
		}
		printf( "\n" );
	}
}
