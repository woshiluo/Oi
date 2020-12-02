#include <cstdio>

#include <algorithm>

long long ex_gcd( long long a, long long b, long long &x, long long &y ) {
	if( b == 0 ) {
		x = 1, y = 0;
		return a;
	}
	long long p = ex_gcd( b, a % b, x, y );
	long long x2 = x, y2 = y;
	x = y; y = x2 - ( a / b ) * y2;
	return p;
}

inline bool solve( long long a, long long b, long long c, long long &x, long long &y ) {
	long long p = ex_gcd( a, b, x, y );
	if( c % p != 0 ) 
		return false;
	long long off = c / p;
	x = x * off; y = y * off;
	long long t = b / p;
	x = ( ( x % t ) + t ) % t;
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1516.in", "r", stdin );
	freopen( "luogu.1516.out", "w", stdout );
#endif
	long long x, y, m, n, L;
	scanf( "%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L );
	long long sol_x, sol_y;
	if( n > m ) {
		std::swap( n, m );
		std::swap( x, y );
	}
	if( solve( m - n, L, ( ( ( y - x ) % L ) + L ) % L, sol_x, sol_y ) ) 
		printf( "%lld\n", sol_x );
	else 
		printf( "Impossible\n" );
}
