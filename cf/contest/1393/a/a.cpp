// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/07 22:43:07 
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
		printf( "%d\n", ( n / 2 ) + 1 );
	}
}
