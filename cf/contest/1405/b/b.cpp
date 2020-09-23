// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/06 22:57:03 
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

const long long N = 1e5 + 1e4;

long long T;
long long n;
long long a[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%lld", &T );
	while( T -- ) {
		scanf( "%lld", &n );
		long long res = 0, ans = 0;
		for( long long i = 1; i <= n; i ++ ) {
			scanf( "%lld", &a[i] );
			if( a[i] == 0 ) 
				continue;
			if( a[i] > 0 ) {
				res += a[i];
			}
			else {
				long long tmp = Min( res, - a[i] );
				res -= tmp;
				ans += ( - a[i] - tmp );
			}
		}
		printf( "%lld\n", ans );
	}
}
