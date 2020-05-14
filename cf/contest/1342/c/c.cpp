// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/26 23:13:32 
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

int T;
int a, b, q, lcm, cnt;
int sum[110000];
long long l, r;

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

long long calc( long long cur ) {
	long long tmp = cur / lcm, less = cur % lcm, res = 0;
	res += 1LL * ( tmp - 1 ) * ( sum[ lcm - 1 ] );
	res += sum[less];
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &a, &b, &q );
		lcm = a * b / gcd( a, b );
		memset( sum, 0, sizeof( sum ) );
		for( int i = 0; i < lcm; i ++ ) {
			if( ( ( i % a ) % b ) != ( ( i % b ) % a ) ) 
				sum[i] ++;
			if( i != 0 )
				sum[i] += sum[ i - 1 ];
		}
		while( q -- ) {
			scanf( "%lld%lld", &l, &r );
			long long ans = calc(r) - calc( l - 1LL );
			printf( "%lld ", ans );
		}
		printf( "\n" );
	}
}
