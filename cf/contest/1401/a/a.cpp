// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/21 22:35:36 
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
		if( n < k ) 
			printf( "%d\n", k - n );
		else 
			printf( "%d\n", ( n - k ) & 1 ) ;
	}
}
