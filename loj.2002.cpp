#include <cstdio>
#include <cstring>

#include <vector>

const int P = 110;
const int M = 2e7 + 1e6;
const int mod = 20170408;

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline int mul( int a, int b ) { return ( 1LL * a * b ) % mod; }

int n, m, p;

struct Matrix {
	int val[P][P];
	Matrix( int cur = 1 ) {
		memset( val, 0, sizeof(val) );
		if( cur != 0 ) {
			for( int i = 1; i <= 100; i ++ ) 
				val[i][i] = cur;
		}
	}
	Matrix operator* ( Matrix _b ) {
		Matrix res(0);
		for( int i = 1; i <= 100; i ++ ) {
			for( int j = 1; j <= 100; j ++ ) {
				for( int k = 1; k <= 100; k ++ ) {
					res.val[i][j] = add( res.val[i][j], mul( val[i][k], _b.val[k][j] ) );
				}
			}
		}
		return res;
	}
};

bool is_prime[M];
std::vector<int> prime;
void pre( int cur ) {
	memset( is_prime, true, sizeof(is_prime) );
	is_prime[1] = false;
	for( int i = 2; i <= cur; i ++ ) {
		if( is_prime[i] ) {
			prime.push_back(i);
		}
		for( auto pri: prime ) {
			if( 1LL * pri * i > cur ) 
				break;
			int nxt = pri * i;
			is_prime[nxt] = false;
			if( i % pri == 0 ) 
				break;
		}
	}
}

Matrix ksm( Matrix a, int p ) {
	Matrix res;
	while( p ) {
		if( p & 1 ) 
			res = a * res;
		a = a * a;
		p >>= 1;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "loj.2002.in", "r", stdin );
	freopen( "loj.2002.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &p );
	Matrix meta(0), fst(0);
	pre(m);
	for( int i = 1; i <= p; i ++ ) {
		meta.val[1][i] = ( m + ( i - 1 ) ) / p;
	}
	for( int i = 2; i <= p; i ++ ) {
		for( int j = 1; j <= p; j ++ ) {
			int la = j - 1;
			if( la == 0 )
				la = p;
			meta.val[i][j] = meta.val[ i - 1 ][la];
		}
	}

	for( auto pri: prime ) {
		fst.val[1][ ( pri % p ) + 1 ] = 1;
		//fst.val[ ( pri % p ) + 1 ][1] = 1;
	}

	Matrix res = fst * ksm( meta, n - 1 );

	printf( "%d\n", res.val[1][p] );
}
