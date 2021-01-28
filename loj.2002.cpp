#include <cstdio>
#include <cstring>

#include <vector>

#define printdebug

const int mod = 20170408;
const int M = 2e7 + 1e6;
const int P = 110;

inline int aabs( int a ) { return a < 0? -a: a; }

struct Modint {
	int cur;
	Modint( int _cur = 0 ) { cur = ( ( _cur % mod ) + mod ) % mod; }

	Modint operator+ ( const Modint &b ) const {
		return ( cur + b.cur ) % mod;
	}
	Modint operator- ( const Modint &b ) const {
		return ( Modint(cur) + Modint( - b.cur ) );
	}
	Modint operator* ( const Modint &b ) const {
		return ( 1LL * cur * b.cur ) % mod;
	}
	void operator+= ( const Modint &b ) {
		cur += b.cur;
		if( cur >= mod ) 
			cur -= mod;
	}
	void operator*= ( const Modint &b ) {
		cur = ( 1LL * cur * b.cur ) % mod;
	}
	void output( const char x = '\n' ) {
		printf( "%d%c", cur, x );
	}
};

struct Matrix {
	Modint val[P][P];
	Matrix( int def = 0 ) {
		memset( val, 0, sizeof(val) );
		if( def != 0 ) {
			for( int i = 0; i < P; i ++ )
				val[i][i] = def;
		}
	}
	Matrix operator* ( const Matrix &b ) const {
		Matrix res = 0;
		for( int i = 0; i < P; i ++ ) {
			for( int j = 0; j < P; j ++ ) {
				for( int k = 0; k < P; k ++ ) {
					res.val[i][k] += val[i][j] * b.val[j][k];
				}
			}
		}
		return res;
	} 
	void operator*= ( const Matrix &b ) {
		(*this) = (*this) * b;
	}

	void debug( int p ) {
#ifdef woshiluo 
#ifdef printdebug
		for( int i = 0; i < p; i ++ ) {
			for( int j = 0; j < p; j ++ ) {
				val[i][j].output(' ');
			}
			printf( "\n" );
		}
			printf( "\n" );
#endif
#endif
	}
};

Matrix pow( Matrix a, int p ) {
	Matrix res = 1;
	while( p ) { 
		if( p & 1 ) 
			res *= a;
		a *= a;
		p >>= 1;
	}
	return res;
}

std::vector<int> prime;
bool is_prime[M];

void pre( int n ) {
	memset( is_prime, true, sizeof(is_prime) );
	is_prime[0] = is_prime[1] = false;
	for( int i = 2; i <= n; i ++ ) {
		if( is_prime[i] ) {
			prime.push_back(i); 
		}
		for( auto x: prime ) {
			if( 1LL * x * i > n )
				break;
			is_prime[ x * i ] = false;
			if( i % x == 0 ) 
				break;
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "loj.2002.in", "r", stdin );
	freopen( "loj.2002.out", "w", stdout );
#endif
	Matrix a, b, c, d;
	int n, m, p;
	scanf( "%d%d%d", &n, &m, &p );
	pre(m);
	//const int base = p;
	for( int i = 0; i < p; i ++ ) {
		for( int j = 0; j < p; j ++ ) {
			int st = ( j - i + p ) % p;
			if( st == 0 ) 
				st = p;
			int val = ( m - st ) / p + 1;
			if( m - st < 0 ) val = 0;
			a.val[i][j] = b.val[i][j] = val;
		}
	}
	for( auto x: prime ) {
		for( int i = 0; i < p; i ++ ) {
			b.val[i][ ( i + x ) % p ] += -1;
		}
	}

	c.val[0][0] = 1;
	d.val[0][0] = 1;

	( ( c * pow( a, n ) ).val[0][0] - ( d * pow( b, n ) ).val[0][0] ).output();
}
