#include <cstdio>

const int N = 1 << 20;
const int mod = 998244353;

int n;
int a[N], b[N], p[N], sum;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline void add_eq( int &a, int b ) { a = ( a + b ) % mod; }
inline void mul_eq( int &a, int b ) { a = ( 1LL * a * b ) % mod; }

int ksm( int a, int p ) {
	int res = 1;
	while( p ) {
		if( p & 1 ) 
			res = mul( res, a );
		a = mul( a, a );
		p >>= 1;
	}
	return res;
}
inline int inv( int a ) { return ksm( a, mod - 2 ); }

void XOR( int *f, int len, int x = 1 ) {
	for( int o = 2, k = 1; o <= len; o <<= 1, k <<= 1 ) {
		for( int i = 0; i < len; i += o ) {
			for( int j = 0; j < k; j ++ ) {
				add_eq( f[ i + j ], f[ i + j + k ] );
				f[ i + j + k ] = add( f[ i + j ], add( - f[ i + j + k ], - f[ i + j + k ] ) );
				mul_eq( f[ i + j ], x ); mul_eq( f[ i + j + k ], x );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "F.in", "r", stdin );
	freopen( "F.out", "w", stdout );
#endif
	scanf( "%d", &n );
	n = 1 << n;
	for( int i = 0; i < n; i ++ ) {
		scanf( "%d", &a[i] );
		sum += a[i];
		b[i] = mod - 1;
	}
	sum = inv(sum);
	for( int i = 0; i < n; i ++ ) {
		p[i] = mul( a[i], sum );
	}

	b[0] = n - 1; p[0] -= 1;
	XOR( b, n ); XOR( p, n );
	for( int i = 0; i < n; i ++ ){ 
		mul_eq( b[i], inv( p[i] ) );
	}
	XOR( b, n, inv(2) );
	for( int i = 0; i < n; i ++ ) {
		printf( "%d\n", ( ( add( b[i], -b[0] ) + mod ) % mod ) );
	}
}
