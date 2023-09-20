#include <cstdio>

const int N = 1 << 18;
const int mod = 998244353;

int n;
int ori_a[N], ori_b[N], a[N], b[N];

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline void add_eq( int &a, int b ) { a = ( a + b ) % mod; }
inline void mul_eq( int &a, int b ) { a = ( 1LL * a * b ) % mod; }

inline int ksm( int a, int p ) {/*{{{*/
	int res = 1; 
	while( p ) {
		if( p & 1 ) 
			res = mul( res, a );
		a = mul( a, a );
		p >>= 1;
	}
	return res;
}
inline int inv( int a ) { return ksm( a, mod - 2 ); }/*}}}*/

void init() {/*{{{*/
	for( int i = 0; i < n; i ++ ) {
		a[i] = ori_a[i];
		b[i] = ori_b[i];
	}
}/*}}}*/

void OR( int f[], int x = 1 ) {/*{{{*/
	 for( int o = 2, k = 1; o <= n; o <<= 1, k <<= 1 ) {
		 for( int i = 0; i < n; i += o ) {
			 for( int j = 0; j < k; j ++ ) {
				 add_eq( f[ i + j + k ], mul( f[ i + j ], x ) );
			 }
		 }
	 }
}/*}}}*/

void ADD( int f[], int x = 1 ) {/*{{{*/
	 for( int o = 2, k = 1; o <= n; o <<= 1, k <<= 1 ) {
		 for( int i = 0; i < n; i += o ) {
			 for( int j = 0; j < k; j ++ ) {
				 add_eq( f[ i + j ], mul( f[ i + j + k ], x ) );
			 }
		 }
	 }
}/*}}}*/

void XOR( int f[], int x = 1 ) {/*{{{*/
	 for( int o = 2, k = 1; o <= n; o <<= 1, k <<= 1 ) {
		 for( int i = 0; i < n; i += o ) {
			 for( int j = 0; j < k; j ++ ) {
				 add_eq( f[ i + j ], f[ i + j + k ] );
				 f[ i + j + k ] = add( f[ i + j ], - add( f[ i + j + k ], f[ i + j + k ] ) );
				 mul_eq( f[ i + j ], x ), mul_eq( f[ i + j + k ], x );
			 }
		 }
	 }
} /*}}}*/

void mul( int _a[], int _b[] ) {/*{{{*/
	for( int i = 0; i < n; i ++ ) {
		mul_eq( _a[i], _b[i] );
	}
}/*}}}*/

void print( int _a[] ) {/*{{{*/
	for( int i = 0; i < n; i ++ ) {
		printf( "%d ", ( _a[i] + mod ) % mod );
	}
	printf( "\n" );
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "luogu.4717.in", "r", stdin );
	freopen( "luogu.4717.out", "w", stdout );
#endif
	scanf( "%d", &n );
	n = 1 << n;
	for( int i = 0; i < n; i ++ ) {
		scanf( "%d", &ori_a[i] );
	}
	for( int i = 0; i < n; i ++ ) {
		scanf( "%d", &ori_b[i] );
	}

	// OR 
	init(); OR( a, 1 ); OR( b, 1 );
	mul( a, b );
	OR( a, -1 );
	print( a );

	// ADD
	init(); ADD( a, 1 ); ADD( b, 1 );
	mul( a, b );
	ADD( a, -1 );
	print( a );

	// XOR 
	init(); XOR( a, 1 ); XOR( b, 1 );
	mul( a, b );
	XOR( a, inv(2) );
	print( a );
}
