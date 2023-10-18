/*
 * f.cpp 2023-10-03
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGmodLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

typedef const int cint;
typedef long long ll;
typedef unsigned long long ull;

using ll = long long;
using vi = std::vector<int>;
using pii = std::pair<int, int>;
template <class T>
using vc = std::vector<T>;
// template <class T>
// using pq = std::priority_queue<T>;
// template <class T>
// using pqg = priority_queue<T, std::vector<T>, greater<T>>;
//
#define rep( i, x, y ) for ( int i = x; i < y; i++ )
#define rp( i, n ) rep( i, 0, n )
#define sz( x ) int( ( x ).size() )
#define all( x ) begin( x ), end( x )

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

const int mod = 37;

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

constexpr int get_map( const char cur ) {
	if( cur >= 'A' && cur <= 'Z' ) 
		return cur - 'A';
	if( cur >= '0' && cur <= '9' )
		return cur - '0' + 26;
	if( cur == ' ' )
		return 36;
	std::exit(-1);
}

constexpr int get_remap( const int cur ) {
	if( cur < 26 ) 
		return cur + 'A';
	if( cur < 36 )
		return ( cur - 26 ) + '0';
	if( cur == 36 ) 
		return ' ';
	std::exit(-1);
}

std::vector<std::vector<ModInt>> pa;

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	int n = read<int>();

	std::string ra, rb;
	std::getline( std::cin, ra );
	std::getline( std::cin, rb );

	const char *a = ra.c_str();
	const char *b = rb.c_str();

	cint lena = strlen(a);
	cint lenb = strlen(b);
	cint size = Max( strlen( a ), strlen(b) ); 

	for( int i = 0, p = 0; i < size; i += n, p ++ ) {
		auto get_a = [&]( cint cur ) {
			if( cur < lena ) 
				return a[cur];
			else
				return ' ';
		};
		auto get_b = [&]( cint cur ) {
			if( cur < lenb ) 
				return b[cur];
			else
				return ' ';
		};
		for( int j = 0; j < n; j ++ ) {
			for( int k = 0; k < 1; k ++ ) {
				std::vector<ModInt> cur( n * n + 1 );
				for(int q = 0; q < n; q ++ ) {
					// mb[j][k] += key[j][q] * ma[q][k]
					cur[ j * n + q ] = get_map( get_a( i + q ) );
				}
				cur[ cur.size() - 1 ] = get_map( get_b( i + j ) );
				pa.push_back(cur);
			}
		}
//		for( int j = 0; j < n; j ++ ) {
//			ma[j][p]  = get_map( get_a( i + j ) );
//			mb[j][p]  = get_map( get_b( i + j ) );
//		}
	}

	cint totx = n * n;
	cint totp = pa.size();
	int cntx = 0;
	for( int i = 0; i <= totx; i ++ ) {
		int p = -1;
		for( int j = cntx; j < totp; j ++ ) {
			if( pa[j][i].cur != 0 ) {
				p = j;
				break;
			}
		}
		if( p == -1 ) {
			continue;
		}
		if( i == totx ) {
			printf( "No solution\n" );
			return 0;
		}
		std::swap( pa[cntx], pa[p] );

		{
			const auto tp = (ModInt)1 / pa[cntx][i];
			for( int k = i; k <= totx; k ++ ) {
				pa[cntx][k] *= tp;
			}
		}
		for( int j = cntx + 1; j < totp; j ++ ) {
			if( pa[j][i].cur == 0 ) 
				continue;
			const auto tp = (ModInt)pa[cntx][i] / pa[j][i];
			for( int k = i; k <= totx; k ++ ) {
				pa[j][k] *= tp;
				pa[j][k] -= pa[cntx][k];
			}
		}
		cntx ++;
	}

	if( cntx < totx ) {
		printf( "Too many solutions\n" );
		return 0;
	}

	std::vector<std::vector<ModInt>> res( n, std::vector<ModInt>(n) );
	for( int i = totx - 1; i >= 0; i -- ) {
		for( int j = i - 1; j >= 0; j -- ) {
			const auto tp = pa[j][i];
			for( int k = i; k <= totx; k ++ ) {
				pa[j][k] -= pa[i][k] * tp;
			}
		}
		res[ i / n ][ i % n ] = pa[i][totx];
	}


	for( int i = 0; i < n; i ++ ) {
		for( int j = 0; j < n; j ++ ) 
			res[i][j].output( ' ' );
		printf( "\n" );
	}
}
