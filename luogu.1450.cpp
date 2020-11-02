#include <cstdio>

const long long S = 1e5 + 1e4;

long long c[10], d[10], n;
long long f[S];

long long bit_cnt( int cur ) {
	int res = 0;
	while( cur ) {
		res += ( cur & 1 );
		cur >>= 1;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1450.in", "r", stdin );
	freopen( "luogu.1450.out", "w", stdout );
#endif
	scanf( "%lld%lld%lld%lld%lld", &c[0], &c[1], &c[2], &c[3], &n );
	f[0] = 1;
	for( long long i = 0; i < 4; i ++ ) {
		for( long long j = c[i]; j < S; j ++ ) {
			f[j] += f[ j - c[i] ];
		}
	}
	for( long long i = 1; i <= n; i ++ ) {
		long long s;
		scanf( "%lld%lld%lld%lld%lld", &d[0], &d[1], &d[2], &d[3], &s );
		long long ans = 0;
		for( int k = 0; k < 16; k ++ ) {
			long long p = ( ( bit_cnt(k) & 1 )? -1LL: 1LL), res = 0;
			for( long long j = 0; j < 4; j ++ ) {
				if( ( k >> j ) & 1LL )
					res += ( d[j] + 1LL ) * c[j];
			}
			if( s - res >= 0 ) 
				ans += f[ s - res ] * p;
		}
		printf( "%lld\n", ans );
	}
}
