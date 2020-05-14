#include <cstdio>

const int N = 1e5 + 1e4;

int T;
int n;
int p[N];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &p[i] );
		}
		for( int i = 2; i <= n; i ++ ) {
			if( p[i] - p[ i - 1 ] > 1 ) {
				flag = false;
				break;
			}
		}
		printf( "%s\n", flag? "Yes": "No" );
	}
}
