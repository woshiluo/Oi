#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using std::make_pair;

inline long long gcd( long long a, long long b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "loj.3144.in", "r", stdin );
	freopen( "loj.3144.out", "w", stdout );
#endif
	int n;
	long long A, B;
	scanf( "%d%lld%lld", &n, &A, &B );
	long long G = ( A * B ) / gcd( A, B + 1 );
	std::vector< std::pair<long long, long long> > seg;
	for( int i = 1; i <= n; i ++ ) {
		long long l, r;
		scanf( "%lld%lld", &l, &r );
		if( r - l + 1 >= G ) {
			printf( "%lld\n", G );
			return 0;
		}
		l = ( l % G ), r = ( r % G );
		if( l <= r ) 
			seg.push_back( make_pair( l, r ) );
		else {
			seg.push_back( make_pair( 0, r ) );
			seg.push_back( make_pair( l, G - 1 ) );
		}
	}
	std::sort( seg.begin(), seg.end() );

	long long cur_r = -1, ans = 0;
	for( auto cur: seg ) {
		long long l = cur.first, r = cur.second;
		if( l > cur_r ) {
			cur_r = l - 1;
		}
		if( r > cur_r ) {
			ans += ( r - cur_r );
			cur_r = r;
		}
	}

	printf( "%lld\n", ans );
}
