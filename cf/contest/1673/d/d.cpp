/*
 * d.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
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
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
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
}/*}}}*/

const int mod = 1e9 + 7;

struct ModInt {/*{{{*/
	int cur;
	ModInt( ll _cur = 0 ) { cur = ( ( ( _cur % mod ) + mod ) % mod ); }

	inline ModInt operator+ ( const ModInt &b ) const { return ( cur + b.cur ) % mod; }
	inline ModInt operator- ( const ModInt &b ) const { return ( ( ( cur - b.cur ) % mod ) + mod ) % mod; }
	inline ModInt operator* ( const ModInt &b ) const { return ( 1LL * cur * b.cur ) % mod; }
	inline ModInt operator/ ( const ModInt &b ) const { return ( 1LL * cur * pow( b, mod - 2 ).cur ) % mod; }

	inline void operator+= ( const ModInt &b ) { (*this) = (*this) + b; }
	inline void operator-= ( const ModInt &b ) { (*this) = (*this) - b; }
	inline void operator*= ( const ModInt &b ) { (*this) = (*this) * b; }
	inline void operator/= ( const ModInt &b ) { (*this) = (*this) / b; }

	inline void output( const char end = '\n' ) { printf( "%d%c", cur, end ); }
};/*}}}*/

ll gcd( const ll a, const ll b ) { return b? gcd( b, a % b ): a; }
ll lcm( const ll a, const ll b ) { return a / gcd( a, b ) * b; }

struct Seq {
	ll st, d, len;

	ll ed() const { return st + ( len - 1 ) * d; }
	bool is_in( const ll &cur ) const {
		if( st <= cur && cur <= ed() ){
			if( ( cur - st ) % d == 0 ) 
				return true;
		}
		return false;
	}
	bool is_sub( const Seq &_b ) const {
		if( _b.is_in(st) && _b.is_in(ed()) && gcd( _b.d, d ) == _b.d ) {
			return true;
		}
		return false;
	}
	ll pre() const { return st - d; }
	ll nxt() const { return ed() + d; }
} b, c;

bool flag;

ModInt work( const ll d ) {
	if( lcm( d, b.d ) < c.d ) 
		return 0;
	return pow( (ModInt)( c.d / d ), 2 );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		{
			int bs = read<int>(); int bd = read<int>(); int bl = read<int>();
			b = (Seq) { bs, bd, bl };
			int cs = read<int>(); int cd = read<int>(); int cl = read<int>();
			c = (Seq) { cs, cd, cl };
		}
		if( !c.is_sub(b) ) {
			printf( "0\n" );
			continue;
		}
		if( c.st - c.d < b.st || c.ed() + c.d > b.ed() ) {
			printf( "-1\n" );
			continue;
		}

		ModInt ans = 0;
		for( int i = 1; 1LL * i * i <= c.d; i ++ ) {
			if( c.d % i != 0 ) 
				continue;
			ans += work(i);
			if( i != c.d / i )
				ans += work( c.d / i );
		}
		ans.output();
	}
}
