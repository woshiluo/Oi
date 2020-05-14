// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/23 22:48:04 
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
T chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
T chk_Min( T &a, T b ) { if( b < a ) a = b; }

int T;
int n, a, b, c, d;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d%d%d", &n, &a, &b, &c, &d );
		int less = ( a - b ) * n, max = ( a + b ) * n;
		int sum_less = c - d, sum_max = c + d;
		if( ( sum_less <= less && less <= sum_max ) || ( sum_less <= max && max <= sum_max ) ||
				( less <= sum_less && sum_less <= max ) || ( less <= sum_max && sum_max <= max ) ) 
			printf( "Yes\n" );
		else 
			printf( "No\n" );
	}
}
