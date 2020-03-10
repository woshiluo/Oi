// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/09 23:21:18 
#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

const int N = 2e5 + 1e4;
const int mod = 998244353;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }
inline void add_eq( int &a, int b ) { a = ( a + b ) % mod; }
inline void mul_eq( int &a, int b ) { a = ( 1LL * a * b ) % mod; }

int ksm( int a, int p ) {
	int res = 1;
	while(p) {
		if( p & 1 ) 
			res = mul( res, a );
		a = mul( a, a );
		p >>= 1;
	}
	return res;
}

inline int get_inv( int a ) { return ksm( a, mod - 2 ); }

int n, m, sum, ans;
int fact[N], inv[N];

void init() {
	fact[1] = 1;
	for( int i = 2; i <= m; i ++ ) {
		fact[i] = mul( fact[ i - 1 ], i );
	}
	inv[m] = get_inv( fact[m] );
	for( int i = m - 1; i >= 1; i -- ) {
		inv[i] = mul( inv[ i + 1 ], i + 1 );
	}
	inv[0] = 1;
	fact[0] = 1;
}

// Get C^a_b
inline int C( int a, int b ) { 
	if( a <= 0 ) 
		return 1;
	if( b <= 0 ) 
		return 1;
	return mul( mul( fact[b], inv[ b - a ] ), inv[a] ); 
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	init();

	for( int i = n - 1; i <= m; i ++ ) {
		add_eq( sum, mul( C( n - 3, i - 2 ), mul( m - i + 1, n - 2 ) ) );
	}

	for( int i = 2; i < n; i ++ ) {
		add_eq( ans, mul( sum, C( i - 2, n - 3 ) ) );
	}

	printf( "%d\n", ans );
}
