/*
 * luogu.3803.cpp
 * 2021-06-22 20:41 
 * woshiluo <woshiluo.luo@outlook.com>
 * Blog: https://blog.woshiluo.com
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( char ch ) { return ch >= '0' && ch <= '9'; }/*{{{*/

template <class T>
T Max( T a, T b ) { return a > b? a: b; }
template <class T>
T Min( T a, T b ) { return a < b? a: b; }
template <class T>
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T>
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <class T>
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 )
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}

template <typename T>
T read() {
	T sum = 0, fl = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}/*}}}*/

const int mod = 998244353;

template <class T>/*{{{*/
inline T inv( T a ) { return pow( a, mod - 2 ); }

struct ModInt {
	int cur;
	ModInt( int _cur = 0 ) { cur = ( _cur + mod ) % mod; }

	ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	ModInt operator- ( const ModInt &b ) const { return ( ( (  cur - b.cur ) % mod ) + mod )  % mod; }
	ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * inv(b).cur ) % mod; }

	void operator+= ( const ModInt &b ) { *this = (*this) + b; }
	void operator-= ( const ModInt &b ) { *this = (*this) - b; }
	void operator*= ( const ModInt &b ) { *this = (*this) * b; }
	void operator/= ( const ModInt &b ) { *this = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

const ModInt G = 3;
struct Poly {
	std::vector<ModInt> a;
	
	Poly( int n ) { a.resize(n); }
	void change() {
		int len = a.size();
		std::vector<int> r; r.resize(len);

		for( int i = 0; i < len; i ++ ) {
			r[i] = ( r[ i >> 1 ] >> 1 );
			if( i & 1 ) 
				r[i] |= ( len >> 1 );
		}

		for( int i = 0; i < len; i ++ ) {
			if( r[i] < i )  
				std::swap( a[i], a[ r[i] ] );
		}
	}

	void ntt( bool on = false ) {
		this -> change();
		int len = a.size();
		for( int h = 2; h <= len; h <<= 1 ) {
			int k = ( h >> 1 );
			ModInt wi = pow( G, ( ( mod - 1 ) / h ) );
			if( on ) 
				wi = (ModInt)1 / wi;
			for( int i = 0; i < len; i += h ) {
				ModInt w = 1;
				for( int j = 0; j < k; j ++ ) {
					const int cur = i + j, nxt = i + j + k;
					const ModInt u = a[cur], v = w * a[nxt];
					
					a[cur] = u + v;
					a[nxt] = u - v;

					w *= wi;
				}
			}
		}

		if( on ) {
			for( auto &x: a ) {
				x /= len;
			}
		}
	}
	void output() {
#ifdef DEBUG
		for( auto &x: a ) {
			x.output( ' ' );
		}
		printf( "\n" );
#endif
	}
};

int main() {
#ifdef woshiluo
	freopen( "3803.in", "r", stdin );
	freopen( "tmp.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	n ++; m ++;
	int len = n + m;
	{
		int tmp = 1;
		for( ; tmp < len; tmp <<= 1 );
		len = tmp;
	}

	Poly a(len), b(len);

	for( int i = 0; i < n; i ++ ) 
		a.a[i] = read<int>();
	for( int i = 0; i < m; i ++ ) 
		b.a[i] = read<int>();

	a.ntt(); b.ntt();
	a.output(); b.output();

	for( int i = 0; i < len; i ++ ) {
		a.a[i] *= b.a[i];
	}

	a.ntt(true);
	for( int i = 0; i < n + m - 1; i ++ ) 
		a.a[i].output( ' ' );

	fclose( stdout );
}
