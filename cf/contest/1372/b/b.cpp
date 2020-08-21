// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/11 23:19:00 
// Blog: https://blog.woshiluo.com

#include <cmath>
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

int t, n;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		int tmp = std::sqrt(n);
		int ans = n;
		for( int i = 1; i <= tmp; i ++ ) {
			if( n % i == 0 ) {
				int less = n - i;
				if( Max( less, i ) < ans ) 
					ans = Max( less, i );

				int tmp_i = n / i;
				less = n - tmp_i;
				if( less == 0 ) 
					continue;
				if( Max( less, tmp_i ) < ans )
					ans = Max( less, tmp_i );
			}
		}
		printf( "%d %d\n", n - ans, ans );
	}
}
