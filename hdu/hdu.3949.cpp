#include <cstdio>
#include <cstring>

#include <vector>
#include <iostream>

typedef long long ll;
typedef unsigned long long ull;

const int MAX_LENGTH = 63;

struct LinearBasis {
	int n = 0, cnt = 0;
	ull a[MAX_LENGTH];
	bool vis[MAX_LENGTH];

	void init( int _n, ll val[] ) {
		n = _n; cnt = 0;
		memset( a, 0, sizeof(a) );
		memset( vis, 0, sizeof(vis) );
		for( int i = 1; i <= _n; i ++)  {
			this -> add( val[i] );
		}
	}
	
	void add( ll cur ) {
		for( int i = MAX_LENGTH - 1; i >= 0; i -- ) {
			if( ( cur & ( 1ull << i ) ) == 0 ) 
				continue;

			if( a[i] ) {
				cur ^= a[i];
				continue;
			}

			cnt ++;
			for( int j = 0; j < i; j ++ ) {
				if( cur & ( 1ull << j ) ) 
					cur ^= a[j];
			}
			for( int j = i + 1; j < MAX_LENGTH; j ++ ) {
				if( a[j] & ( 1ull << i ) ) 
					a[j] ^= cur;
			}

			a[i] = cur;
			vis[i] = true;
			break;
		}
	}

	ll query( ll k ) {
		if( cnt != n ) {
			k --;
		}

		if( k >= ( 1ll << cnt ) ) 
			return -1;

		ll res = 0;
		for( int i = 0; i < MAX_LENGTH; i ++ ) {
			if( vis[i] && ( ( 1ull << i ) & k ) ) {
				res ^= a[i];
			}
		}

		return res;
	}
} linear;

void readin() {
	int n;

	scanf( "%d", &n );
	ll *a = new ll[ n + 10 ];
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%lld", &a[i] );
	}

	linear.init( n, a );

	delete [] a;
}

void work() {
	int m;
	scanf( "%d", &m );
	while( m -- ) {
		ll k;
		scanf( "%lld", &k );

		printf( "%lld\n", linear.query(k) );
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.3949.in", "r", stdin );
	freopen( "hdu.3949.out", "w", stdout );
#endif

	int T;
	scanf( "%d", &T );
	for( int i = 1; i <= T; i ++ ) {
//		printf( "Case #%d:\n", i );
		std::cout<< "Case #" << i << ":" << std::endl;
		readin();
		work();
	}
}
