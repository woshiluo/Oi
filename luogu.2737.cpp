#include <cstdio>

#include <algorithm>

const int N = 20;
const int MAX = 1e6;

int n;
int a[N];
bool f[MAX];

inline int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }
inline int lcm( int a, int b ) { 
	int a_b_gcd = gcd( a, b );
	return a * b / a_b_gcd;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.2737.in", "r", stdin );
	freopen( "luogu.2737.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	int max = (int) 1e6;
	bool flag = false;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			if( gcd( a[i], a[j] ) == 1 ) {
				flag = true;
				max = std::min( lcm( a[i], a[j] ), max );
			}
		}
	}
	if( flag == false ) {
		printf( "0" );
		return 0;
	}
	f[0] = true;
	std::sort( a + 1, a + n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = a[i]; j <= max; j ++ ) {
			f[j] |= f[ j - a[i] ];
		}
	}
	int ans = 0;
	for( int i = 1; i <= max; i ++ ) {
		if( f[i] == false ) {
			ans = std::max( ans, i );
		}
	}
	printf( "%d\n", ans );
}
