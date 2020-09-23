// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/01 00:31:59 
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

const int N = 1e6 + 1e5;

long long n, r1, r2, r3, d;
long long a[N], b[N], c[N];
long long f[N][3];
// b[] / 0 => kill all in once
// c[] / 1 => kill all in twice

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	scanf( "%lld%lld%lld%lld%lld", &n, &r1, &r2, &r3, &d );
	long long min_3 = Min( r1, Min( r2, r3 ) );
	for( long long i = 1; i <= n; i ++)  {
		scanf( "%lld", &a[i] );
		b[i] = a[i] * Min( r1, r3 ) + r3;
		c[i] = Min( r2 + min_3, Min( r1, r3 ) * a[i] + Min( r1, r2 ) * 2LL );
	}
	f[0][1] = f[0][2] = (long long)(1e18);
	for( long long i = 1; i <= n; i ++ ) {
		f[i][0] = Min( f[ i - 1 ][0] + b[i], f[ i - 1 ][1] + Min( b[i], c[i] ) ) + d;
		f[i][1] = Min( f[ i - 1 ][0] + c[i], f[ i - 1 ][1] + Min( b[i], c[i] ) ) + 3LL * d;
		f[i][2] = Min( f[ i - 1 ][0] + c[i], f[ i - 1 ][2] + Min( b[i], c[i] ) ) + 2LL * d;
	}

	printf( "%lld\n", Min( f[n - 1][2] + b[n], 
				Min( f[n][0] - d, f[ n - 1 ][0] + c[n] + 2LL * d ) ) );
}
