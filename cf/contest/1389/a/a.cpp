// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/29 22:38:11 
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
int a, b;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &a, &b );
		if( a * 2 <= b ) 
			printf( "%d %d\n", a, a << 1 );
		else 
			printf( "-1 -1\n" );
	}
}
