// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/29 23:55:01 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

inline long long aabs( long long a ) { return a < 0? ( - a ): a; }
template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> void chk_Min( T &a, T b ) { if( b < a ) a = b; }

struct node {
	long long x, y;
	long long contains( node b ) { return ( Min( y, b.y ) - Max( x, b.x ) ); }
} a, b;
long long T, n, k;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%lld", &T );
	while( T -- ) {
		scanf( "%lld%lld", &n, &k );
		scanf( "%lld%lld", &a.x, &a.y );
		scanf( "%lld%lld", &b.x, &b.y );

		long long base = Max(a.contains(b) * n, 0LL);
		if( base > k ) {
			printf( "0\n" );
			continue;
		}

		if( a.contains(b) >= 0LL ) {
			long long tmp = ( Max( a.y, b.y ) - Min( a.x, b.x ) ) - a.contains(b);
			if( tmp * n >= k ) 
				printf( "%lld\n", base + k );
			else {
				long long less = k - tmp * n;
				printf( "%lld\n", base + tmp * n + ( less * 2LL ) );
			}
			continue;
		}

		if( a.x > b.x ) 
			std::swap( a, b );

		long long min_step = ( b.x - a.y );
		long long contrib = aabs( b.y - a.x );
		long long res = min_step;

		if( contrib >= k ) {
			printf( "%lld\n", base + contrib + res + k );
			continue;
		}
		else {
			k -= contrib;
			res += contrib;
		}
		long long less = n - 1LL;
		while( k > 0 ) {
			long long user_contrib = min_step + Min( k, contrib );
			long long bf = Min(contrib,k) * 2LL;
			long long tmp = 0;

			if( less > 0 && user_contrib < bf ) {
				less --;
				tmp = user_contrib;
			}
			else
				tmp = bf;

			res += tmp;
			k -= contrib;
		}

		printf( "%lld\n", base + res );
	}
}
