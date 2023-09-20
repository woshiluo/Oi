/*
 * c.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
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
	for (; !isdigit(ch); ch = getchar())
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

struct Matrix;
Matrix pow( Matrix a, int p );
// front up right left down back
struct Matrix {
	int a[6]; ll cnt[6];
	Matrix operator* ( const Matrix &b ) const { 
		Matrix res;
		for( int i = 0; i < 6; i ++ ) 
			res.a[i] = a[ b.a[i] ];
		for( int i = 0; i < 6; i ++ ) 
			res.cnt[i] = b.cnt[i] + cnt[ b.a[i] ];
		return res;
	}
	void operator*= ( const Matrix &b ) {
		*this = (*this) * b;
	}
};

Matrix pow( Matrix a, int p ) {
	Matrix res = (Matrix){ { 0, 1, 2, 3, 4, 5 }, { 0, 0, 0, 0, 0 ,0 } };
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}


int a[6];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	Matrix up = (Matrix){ { 4, 0, 2, 3, 5, 1 }, { 0, 0, 0, 0, 1, 0 } };
	Matrix rig = (Matrix){ { 0, 3, 1, 4, 2, 5 }, { 0, 0, 0, 0, 1 ,0 } };
	Matrix res = (Matrix){ { 0, 1, 2, 3, 4, 5 }, { 0, 0, 0, 0, 0 ,0 } }; 

	ll n, m;
	n = read<ll>(); m = read<ll>();
	for( int i = 0; i < 6; i ++ ) 
		a[i] = read<int>();

	while( n > 1 && m > 1 ) {
		if( n > m ) {
			Matrix tmp = pow( rig, n / m );
			res *= tmp;
			up *= tmp;
			n %= m;
		}
		else {
			Matrix tmp = pow( up, n / m );
			res *= tmp;
			rig *= tmp;
			m %= n;
		}
	}
	if( n == 1 ) 
		res *= pow( up, m - 1 );
	else 
		res *= pow( rig, n - 1 );

	ll ans = 0;
	for( int i = 0; i < 6; i ++ ) {
		ans += a[ res.a[i] ] * res.cnt[i];
	}

	printf( "%lld\n", ans );
}
