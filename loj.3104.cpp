#include <cstdio>
#include <cstring>

const int K = 30;
const int mod = 1e9 + 7;
const int LEN = 1e5 + 1e4;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }

long long n;
char s[LEN];

struct matrix {
	int a[K][K];
	matrix( int k = 0 ) {
		memset( a, 0, sizeof(a) );
		if( k != 0 ) 
			for( int i = 0; i < K; i ++ ) 
				a[i][i] = k;
	}
	matrix operator* ( const matrix &b ) const {
		matrix res(0);
		for( int i = 0; i < 26; i ++ ) {
			for( int j = 0; j < 26; j ++ ) {
				for( int k = 0; k < 26; k ++ ) {
					res.a[i][j] = add( res.a[i][j], mul( this -> a[i][k], b.a[k][j] ) );
				}
			}
		}
		return res;
	}
} f;

matrix ksm( matrix a, long long p ) {
	matrix res(1);
	while( p ) {
		if ( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "loj.3104.in", "r", stdin );
	freopen( "loj.3104.out", "w", stdout );
#endif
	scanf( "%lld", &n );
	scanf( "%s", s );

	for( int i = 0; i < 26; i ++ ) {
		for( int j = 0; j < 26; j ++ ) {
			f.a[i][j] = 1;
		}
	}

	int len = strlen(s);
	for( int i = 0; i < len - 1; i ++ ) 
		f.a[ s[i] - 'a' ][ s[ i + 1 ] - 'a' ] = 0;

	f = ksm( f, n - 1 );
	int ans = 0;
	for( int i = 0; i < 26; i ++ ) {
		for( int j = 0; j < 26; j ++ ) {
			ans = add( ans, f.a[i][j] );
		}
	}
	printf( "%d\n", ( ans + mod ) % mod );
}
