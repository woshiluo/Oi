// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/30 23:21:14 
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

const int N = 1e5 + 1e4;

long long n;
long long a[N];
long long fir[N], sec[N];

long long ex_gcd(long long a, long long b, long long& x, long long& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	long long d = ex_gcd(b, a % b, x, y);
	long long temp = x;
	x = y;
	y = temp - a / b * y;
	return d;
}

int main() {
	scanf( "%lld", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}
	long long t1 = 0, t2 = 0;
	ex_gcd( n, 1, t1, t2 );
	fir[1] = t1 * a[1];
	sec[1] = t2 * a[1];
	long long b = n - 1;
	for( int i = 2; i <= n; i ++ ) {
		long long t1 = 0, t2 = 0;
		ex_gcd( n, b, t1, t2 );
		fir[i] = t1 * a[i];
		sec[i] = t2 * a[i];
	}
	printf( "%d %lld\n", 1, n );
	for( int i = 1; i <= n; i ++ ) {
		printf( "%lld ", -fir[i] * n );
	}
	printf( "\n%d %d\n", 1, 1 );
	printf( "%lld", -sec[1] );
	if( n == 1 ) {
		printf( "\n1 1\n0" );
		return 0;
	}
	printf( "\n%d %lld\n", 2, n );
	for( int i = 2; i <= n; i ++ ) {
		printf( "%lld ", -sec[i] * b );
	}
}
