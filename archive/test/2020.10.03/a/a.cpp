#include <cstdio>
#include <cstdlib>

int n, m, k;
int a[N], b[N];

void Impossible() {
	puts( "Impossible" );
	exit(0);
}

int main() {
	scanf( "%d%d%d", &n, &m, &k );
	int base = 0, ext = 0;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		if( a[i] < k ) 
			Impossible();
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
	}
	std::sort( b + 1, b + n + 1 );
}
