#include <cstdio>

const int N = 1e6 + 1e5;

int f[N];

inline int calc( int cur ) {
	int cnt = 0;
	while( cur ) {
		cnt += ( cur % 10 );
		cur /= 10;
	}
	return cnt;
}

int main() {
	freopen( "number.in", "r", stdin );
	freopen( "number.out", "w", stdout );

	int n;
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		f[i] ++;
		f[ i + calc(i) ] += f[i];
	}
	printf( "%d\n", f[n]) ;

	fclose( stdin );
	fclose( stdout );
	return 0;
}
