// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/17 22:39:20 
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
		int n, c0, c1, h;
		scanf( "%d%d%d%d", &n, &c0, &c1, &h );
		long long ans = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%1d", &tmp );
			if( tmp == 0 ) {
				if( c0 - c1 >= h ) {
					tmp = 1;
					ans += h;
				}
			}
			else {
				if( c1 - c0 >= h ) {
					tmp = 0;
					ans += h;
				}
			}
			ans += ( tmp == 0 )? c0: c1;
		}
		printf( "%lld\n", ans );
	}
}
