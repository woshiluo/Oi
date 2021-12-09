#include <cstdio>

const int mod = 998244353;

template <class T> 
class pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}

struct ModInt {
	int cur;
	ModInt( int _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) const { cur = ( cur + b.cur ) % mod; }
	inline void operator-= ( const ModInt &b ) const { cur = ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline void operator*= ( const ModInt &b ) const { cur = ( 1LL * cur * b.cur ) % mod; }
	inline void operator/= ( const ModInt &b ) const { cur = ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }
};

struct Edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int n, k;

// pick m in n
ModInt C( int n, int m ) { return fac[m] * inv[ m - n ] * inv[n]; }

void dfs( int cur, int la, int x ) {
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur, x );
	}

	static int tmp[N];
	for( int i = ehead[cur]; i; i = e[i].next ) {
		for( int i = 0; i < 
	}
}

int main() {
	scanf( "%d%d" ,&n, &k );
	for( int i = 1; i < n; i ++ ) {
		int u, v;
		scanf( "%d%d", &u, &v );
		add_edge( u, v ); add_edge( v, u );
	}
	
	for( int i = 1; i <= n; i ++ ) {
		fac[i] = fac[ i - 1 ] * i;
	}
	fnv[n] = pow( fac[n], mod - 2 );
	for( int i = n - 1; i >= 1; i -- ) {
		fav[i] = fav[ i + 1 ] * ( i + 1 );
	}

	for( int i = 0; i <= n; i ++ ) {
	}
}
