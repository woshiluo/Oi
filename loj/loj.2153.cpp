#include <cstdio>

#include <vector>

int n, k;
long long f[20][ ( 1 << 11 ) ][100];

std::vector<int> sta;

inline int add( int k, int a ) { return k | ( 1 << a ); }
inline int full_bit( int k ) { return ( 1 << k ); }
inline bool has( int k, int a ) { return ( k >> a ) & 1; }


bool check( int last, int cur ) {
	for( int i = 0; i < k; i ++ ) {
		if( has( cur, i ) ) {
			bool flag = has( last, i );
			if( i > 0 ) 
				flag = ( flag || has( last, i - 1 ) );
			if( i + 1 < k ) 
				flag = ( flag || has( last, i + 1 ) );
			if( flag ) 
				return false;
		}
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "loj.2153.in", "r", stdin );
	freopen( "loj.2153.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 0; i < full_bit(n); i ++ ) {
		bool flag = true;
		for( int j = 1; j < n; j ++ ) {
			int cnt = has( i, j ) + has( i, j - 1 );
			if( cnt > 1 ) {
				flag = false;
				break;
			}
		}
		if( flag ) 
			sta.push_back(i);
	}

	long long ans = 0;
	f[0][0][0] = 1;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j <= k; j ++ ) {
			for( auto s: sta ) {
				for( auto la_s: sta ) {
//					if( check( s, la_s ) == false ) 
					if( ( ( la_s << 1 ) & s ) || 
							( ( la_s >> 1 ) & s ) ||
							( la_s & s ) )
						continue;
					int cur = __builtin_popcount(s);
					if( j - cur < 0 ) 
						continue;
					f[i][s][j] += f[ i - 1 ][la_s][ j - cur ];
				}
			}
		}
	}

	for( auto s: sta ) {
		ans += f[n][s][k];
	}

	printf( "%lld\n", ans );
}
