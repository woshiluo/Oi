#include <cmath>
#include <cstdio>

const int N = 1e5 + 1e4;

int n, g;
int mod_list[] = { 2, 3, 4679, 35617 };

int ksm( int a, int p, int mod ) {
	int res = 1;
	while( p ) {
		if( p & 1 ) 
			res = ( 1LL * res * a ) % mod;
		a = ( 1LL * a * a ) % mod;

		p >>= 1;
	}
	return res;
}

inline int get_inv( int a, int mod ) {
	return ksm( a, mod - 2, mod );
}

namespace get_c {/*{{{*/
	int mod;
	int fact[N], fact_inv[N];

	int lucas( int n, int m ) {
		if( n < m ) 
			return 0;
		if( n < mod ) 
			return ( 1LL * fact[n] * fact_inv[ n - m ] * fact_inv[m] ) % mod;
		return ( 1LL * lucas( n / mod, m / mod ) * lucas( n % mod, m % mod ) ) % mod;
	}
	void init( int n ) {
		fact[0] = 1;
		for( int i = 1; i <= n; i ++ ) {
			fact[i] = ( 1LL * fact[ i - 1 ] * i ) % mod;
		}
		fact_inv[n] = get_inv( fact[n], mod );
		for( int i = n - 1; i >= 0; i -- ) {
			fact_inv[i] = ( 1LL * fact_inv[ i + 1 ] * ( i + 1 ) ) % mod;
		}
	}
	int calc( int _mod ) {
		mod = _mod;
		init( mod - 1 );

		int res = 0;
		for( int left = 1; left <= std::sqrt(n); left ++ ) {
			if( n % left == 0 ) {
				int rig = n / left;

				res = ( res + lucas( n, left ) ) % mod;
				if( left == rig ) 
					continue;
				res = ( res + lucas( n, rig ) ) % mod;
			}
		}

		return res;
	}
}/*}}}*/

int get_crt( int n_list[], int a_list[], int cnt ) {/*{{{*/
	int m[cnt], c[cnt];
	int count_n = 1;
	for( int i = 0; i < cnt; i ++ ) {
		count_n *= n_list[i];
	}
	for( int i = 0; i < cnt; i ++ ) {
		m[i] = count_n / n_list[i];
		c[i] = m[i] * get_inv( m[i], n_list[i] );
	}
	int res = 0;
	for( int i = 0; i < cnt; i ++ ) {
		res = ( res + ( ( 1LL * a_list[i] * c[i] ) % count_n ) ) % count_n;
	}
	return res;
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "luogu.2480.in", "r", stdin );
	freopen( "luogu.2480.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &g );
	if( g % 999911659 == 0 ) {
		printf( "0" );
		return 0;
	}
	int res[4];
	for( int i = 0; i < 4; i ++ ) {
		res[i] = get_c::calc( mod_list[i] );
	}

	int p = get_crt( mod_list, res, 4 );
	printf( "%d\n", ksm( g, p, 999911659 ) );
}
