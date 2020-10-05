#include <cmath>
#include <cstdio>

#include <vector>
#include <algorithm>

const int N = 1e5 + 1e4;

int n, m, q;
std::vector<int> p[N];

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }
long long lcm( int a, int b )  { return 1LL * a * b / gcd( a, b ); }

void init() {
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= std::sqrt(i); j ++ ) {
			if( ( i % j ) == 0 ) {
				p[i].push_back(j);
				if( ( i / j ) != j ) 
					p[i].push_back( i / j );
			}
		}
	}
}

int query( int x, int y ) {
	int ans = 1;
	for( auto a: p[x] ) {
		for( auto b: p[y] ) {
			if( a <= m && b <= m && lcm( a, b ) <= n ) { 
				ans = std::max( ans, std::min( a, b ) );
			}
		}
	}
	return m - ans + 1;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &q );
	init();
	while( q -- ) {
		int x, y;
		scanf( "%d%d", &x, &y );
		printf( "%d\n", query( x, y ) );
	}
}
