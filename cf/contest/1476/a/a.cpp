// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 22:42:20 
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
		int n, k;
		scanf( "%d%d", &n, &k );
		if( n > k ) {
			k = ( ( n / k ) + ( n % k != 0 ) ) * k;
		}
		printf( "%d\n", k / n + ( k % n != 0 ) );
	}
}
