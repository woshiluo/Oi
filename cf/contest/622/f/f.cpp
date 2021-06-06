// Woshiluo<woshiluo@woshiluo.site>
// 2021/05/28 15:31:42 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

const int mod = 1e9 + 7;
const int K = 1e6 + 1e5;

template <class T>
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

template <class T>
inline T inv( T a ) { return ksm( a, mod - 2 ); }

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
};


ModInt f[K], x[K], a[K], b[K], fact[K];
// a / b

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n, k;
	n = read<int>(); k = read<int>();
	ModInt tot_x = 1;
	for( int i = 1; i <= k + 2; i ++ ) {
		f[i] = f[ i - 1 ] + ksm( (ModInt)i, k );
	}

	fact[0] = 1;
	for( int i = 1; i <= k + 2; i ++ ) 
		fact[i] = fact[ i - 1 ] * i;

	for( int i = 1; i <= k + 2; i ++ ) {
		x[i] = ( n - i );
		tot_x *= x[i];
	}

	if( n <= k + 2 ) {
		f[n].output();
	}
	else {
		ModInt ans = 0;
		for( int i = 1; i <= k + 2; i ++ ) {
			ans += ( f[i] * tot_x / x[i] / fact[ k + 2 - i ] / fact[ i - 1 ] ) * ( ( k + 2 - i ) % 2 == 0? 1: -1 );
		}
		ans.output();
	}

}
