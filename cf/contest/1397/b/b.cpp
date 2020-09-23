// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/30 22:43:38 
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
template <class T> 
T aabs( T a ) { return a < 0? -a: a; }

const int N = 1e5 + 1e4;

int n;
long long a[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	bool flag = true;
	const long long MAX = 1e18;
	long long ans = (long long)(1e18);
	std::sort( a + 1, a + n + 1 );

	for( int c = 1; c <= 100000; c ++ ) {
		long long tmp = 1, res = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( tmp >= MAX ) {
				flag = false;
				break;
			}
			res += aabs( tmp - a[i] );
			tmp *= 1LL * c;
		}
		if( flag ) {
			ans = Min( ans, res );
		}
	}
	printf( "%lld\n", ans );
}
