// Woshiluo<woshiluo@woshiluo.site>
// 2020/06/28 11:06:35 
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

int t;
int n;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		if( n % 4 == 0 ) 
			printf( "YES" );
		else 
			printf( "NO" );
		printf("\n");
	}
}
