#include <cstdio>

typedef long long ll;
typedef __int128 lll;

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		ll xor_y = 0;
		lll sum_x = 0, sum_z = 0;
		for( int i = 1; i <= n; i ++ ) {
			ll x, y, z;
			scanf( "%lld%lld%lld", &x, &y, &z );
			sum_x += x; sum_z += z; xor_y ^= y;
		}

		if( sum_x > sum_z ) 
			printf( "100" );
		else if( sum_x < sum_z ) 
			printf( "0" );
		else 
			printf( "%d", xor_y == 1? 60: 40 );
		printf( "\n" );
	}
}
