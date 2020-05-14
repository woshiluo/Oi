// Woshiluo<woshiluo@woshiluo.site>
// 2020/05/01 22:38:07 
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

int T, n;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int n2 = n / 2, a = 0, b = 0;
		for( int i = n - 1, cnt = 1; cnt <= n2; cnt ++, i -- ) {
			a += 1 << i;
		}
		b = 1 << n;
		for( int i = 1; i <= n - 1 - n2; i ++ ) 
			b += 1 << i;
		printf( "%d\n", b - a );
	}
}
