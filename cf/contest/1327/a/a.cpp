#include <cstdio>

int t;
int n, k;

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d%d", &n, &k );
		if( k > n ) 
			printf( "NO\n" );
		else {
			long long tmp = n - k;
			long long sum = ( 1LL * ( ( k - 1 ) * 2LL ) * k ) / 2LL;
			if( sum <= tmp && ( ( tmp - sum ) % 2 == 0 ) ) 
				printf( "YES\n" );
			else 
				printf( "NO\n" );
		}
	}
}
