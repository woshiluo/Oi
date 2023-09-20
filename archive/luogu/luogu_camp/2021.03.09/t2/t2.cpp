#include <cstdio>
#include <cstring>

const int N = 10;
const int S = 1e5 + 1e4;
const int mod = 1e9 + 7;

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
T chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
T chk_Max( T &a, T b ) { if( a < b ) a = b; }
template<class T> 
T ksm( T a, int p ) {
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
	ModInt( int _cur = 0 ) { cur = ( ( _cur % mod ) + mod ) % mod; };
	ModInt operator + ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator - ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	ModInt operator * ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator / ( const ModInt &b ) const { return *this * ksm( b, mod - 2 ); }
	void operator += ( const ModInt &b ) { this -> cur = ( *this + b ).cur; }
	void operator -= ( const ModInt &b ) { this -> cur = ( *this - b ).cur; }
	void operator *= ( const ModInt &b ) { this -> cur = ( *this * b ).cur; }
	void operator /= ( const ModInt &b ) { this -> cur = ( *this / b ).cur; }

	bool operator == ( const ModInt &b ) { return cur == b.cur; }
	void print( char end = '\n' ) {
		printf( "%d%c", cur, end );
	}
};

inline ModInt fac( int n ) {
	ModInt res = 1;
	for( int i = 1; i <= n; i ++ )
		res *= i;
	return res;
}

inline ModInt A( int m, int n ) {
	ModInt res = 1;
	for( int i = 0; i < n; i ++ ) {
		res *= ( m - i );
	}
	return res;
}

inline ModInt C( int m, int n ) { return A( m, n ) / fac(n); }

struct Matrix {
	ModInt a[N][N];

	Matrix( ModInt cur = 0 ) {
		memset( a, 0, sizeof(a) );
		for( int i = 0; i < N; i ++ ) {
			a[i][i] = cur;
		}
	}
	Matrix( int _cur = 0 ) {
		ModInt cur = _cur;
		memset( a, 0, sizeof(a) );
		for( int i = 0; i < N; i ++ ) {
			a[i][i] = cur;
		}
	}

	Matrix operator* ( const Matrix &b ) const {
		Matrix res = 0;
		for( int i = 0; i < N; i ++ ) {
			for( int j = 0; j < N; j ++ ) {
				for( int k = 0; k < N; k ++ ) {
					res.a[i][k] += a[i][j] * b.a[j][k];
				}
			}
		}
		return res;
	}
};

// Template end

int len, k;
ModInt tot;
ModInt res[N];
int cnt[N];
char tmp_str[S];

ModInt test( int type, int a ) { return  a? ( 1 << ( a - 1 ) ): type ^ 1; }

void dfs( int cur_n, int depth, int count ) {
	if( depth == cur_n ) {
		if( count == cur_n )
			return ;
		int cnt_1 = 0;
		for( int i = 0; i < count; i ++ ) 
			cnt_1 += ( cnt[i] & 1 );
		res[cur_n] -= res[cnt_1] * A( (tot - cnt_1).cur, count - cnt_1 );
		return ;
	}
	for( int i = 0; i <= count; i ++ ) {
		cnt[i] ++;
		dfs( cur_n, depth + 1, count + ( count == i ) );
		cnt[i] --;
	}
}

void calc( int n ) {
	if( n < 2 ) {
		res[n] = 1;
		return ;
	}
	Matrix p[2] = { 0, 0 }, base = 1;
	for( int i = 0; i <= n; i ++ ) {
		p[0].a[i][i] = test( 0, n - i );
		for( int j = i; j <= n; j ++ ) {
			p[1].a[i][j] = test( i & 1, n - j ) * C( j, i );
		}
	}
	for( int i = 0; i < len; i ++ ) {
		base = p[ tmp_str[i] - '0' ] * base;
	}
	Matrix ans = ksm( base, k );
	res[n] = ans.a[0][n];
	dfs( n, 0, 0 );
}

int main() {
#ifdef woshiluo 
	freopen( "t2.in", "r", stdin );
	freopen( "t2.out", "w", stdout );
#endif
	int n;
	scanf( "%d%d", &n, &k );
	scanf( "%s", tmp_str );
	len = strlen( tmp_str );

	for( int i = 0; i < len; i ++ ) 
		tot = ( tot * 2 ) + ( tmp_str[i] - '0' );

	ModInt a = ksm( ModInt(2), len ), b = tot;
	for( int i = 1; i < k; i ++ )
		tot = ( tot * a ) + b;

	for( int i = 0; i <= n; i ++ ) 
		if( ( ( n - i ) & 1 ) == 0 ) 
			calc(i);

	( res[n] / fac(n) ).print();
}
