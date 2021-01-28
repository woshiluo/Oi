// Woshiluo<woshiluo@woshiluo.site>
// 2020/12/17 22:41:33 
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
		int a, b, c;
		scanf( "%d%d%d", &a, &b, &c );
		int sum = a + b + c, min = Min( a, Min( b, c ) );
		if( sum % 9 == 0 && ( sum / 9 <= min ) )
			printf( "YES\n" );
		else 
			printf( "NO\n" );
	}
}
