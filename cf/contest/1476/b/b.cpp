// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/29 22:46:45 
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

double pow( double a, long long p ) {
	double res = 1.0;
	for( long long i = 1; i <= p; i ++ ) {
		res *= a;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	long long T;
	scanf( "%lld", &T );
	while( T -- ) {
		long long n, k, sum = 0, ans = 0;
		scanf( "%lld%lld", &n, &k );
		for( long long i = 1; i <= n; i ++ ) {
			long long tmp;
			scanf( "%lld", &tmp );
			if( i != 1 ) {
				if( tmp * 100LL > sum * k ) {
					long long gol = ( ( 100LL * tmp ) / k + ( ( tmp * 100LL ) % k != 0 ) );
					ans += ( gol - sum );
					sum = gol;
				}
			}
			sum += tmp;
		}
		printf( "%lld\n", ans );
	}
}
