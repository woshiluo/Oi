/*
 * b.cpp
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

#include <array>
#include <vector>
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

struct Opt { int n; ll val; };

typedef std::vector<Opt> oplist;
typedef std::vector<int> vecint;

void merge( oplist &ops, vecint &a, int from, int to, ll g ) {/*{{{*/
	if( to - from + 1 == 8 ) {
		merge( ops, a, from, from + 3, g );
		merge( ops, a, from + 4, to, g );
		return ;
	}
	std::swap( a[from + 2], a[from + 3] );
	ops.push_back( { from + 2, -1 } );
	ops.push_back( { from + 1, g - a[from] } );
	ops.push_back( { from + 3, g - a[ from + 3 ] } );
}/*}}}*/

void update_back( vecint &a, oplist &ops ) {/*{{{*/
	const int st = a.size() - 3;
	const ll x = a[st];
	const ll y = a[st + 1];
	const ll z = a[st + 2];
	ops.push_back( { st + 1, - y + z } );
	ops.push_back( { st + 2, x - y } );
}/*}}}*/

void print( vecint &a, oplist &ops ) {/*{{{*/
	for( auto &x: a ) {
		printf( "%d ", x );
	}
	printf( "\n" );
	printf( "%lu\n", ops.size() );
	for( auto &op: ops ) {
		printf( "%d %lld\n", op.n, op.val );
	}
}/*}}}*/

void solve1( const int n ) {/*{{{*/
	const int k = n / 12;
	const int g = 6 * k + 1;
	vecint a; oplist ops;
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( i );
		a.push_back( 2 * k + 1 - i );
		a.push_back( 8 * k + 2 - 2 * i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 2 * k + i );
		a.push_back( 4 * k + 2 - i );
		a.push_back( 8 * k + 3 - 2 * i );
		update_back(a, ops);
	}
	for( int i = 1; i < k; i ++ ) {
		a.push_back( 6 * k + 1 - 2 * i );
		a.push_back( 11 * k + 2 - i );
		a.push_back( 11 * k + 2 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 6 * k + 2 - 2 * i );
		a.push_back( 9 * k + 3 - i );
		a.push_back( 9 * k + 2 + i );
		update_back(a, ops);
	}
	if(k) {
		a.push_back( 3 * k + 1 );
		a.push_back( 8 * k + 2 );
		a.push_back( 11 * k + 2 );
		update_back(a, ops);
	}
	a.push_back( 6 * k + 1 );
	int p = a.size();
	for( int i = 12 * k + 2; i <= n; i ++ ) {
		a.push_back(i);
	}
	if( (int)a.size() != p ) {
		merge( ops, a, p, a.size() - 1, g );
	}

	print( a, ops );
}/*}}}*/

void solve3( const int n ) {/*{{{*/
	const int k = n / 12;
	// const int g = 6 * k + 2;
	vecint a; oplist ops;
	for( int i = 1; i <= k; i ++ ) {
		a.push_back(i);
		a.push_back( 4 * k + 1 + 2 * i );
		a.push_back( 10 * k + 3 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( k + i);
		a.push_back( 6 * k + 1 + 2 * i );
		a.push_back( 11 * k + 3 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 2 * k + i);
		a.push_back( 4 * k + 2 * i );
		a.push_back( 8 * k + 2 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 3 * k + 1 + i);
		a.push_back( 6 * k + 2 + 2 * i );
		a.push_back( 9 * k + 3 + i );
		update_back(a, ops);
	}
	{
		a.push_back( 3 * k + 1 );
		a.push_back( 6 * k + 2 );
		a.push_back( 9 * k + 3 );
		update_back(a, ops);
	}
	print( a, ops );
}/*}}}*/

void solve4( const int n ) {/*{{{*/
	const int k = ( n % 12 == 0 )?( ( n - 12 ) / 12 ): ( n / 12 );
	const int g = 6 * k + 2;
	vecint a; oplist ops;
	for( int i = 1; i <= k; i ++ ) {
		a.push_back(i);
		a.push_back( 4 * k + 1 + 2 * i );
		a.push_back( 10 * k + 3 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( k + i);
		a.push_back( 6 * k + 1 + 2 * i );
		a.push_back( 11 * k + 3 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 2 * k + i);
		a.push_back( 4 * k + 2 * i );
		a.push_back( 8 * k + 2 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 3 * k + 1 + i);
		a.push_back( 6 * k + 2 + 2 * i );
		a.push_back( 9 * k + 3 + i );
		update_back(a, ops);
	}
	{
		a.push_back( 3 * k + 1 );
		a.push_back( 9 * k + 3 );
		a.push_back( 12 * k + 4 );
		update_back(a, ops);
	}
	a.push_back( 6 * k + 2 );
	int p = a.size();
	for( int i = 12 * k + 5; i <= n; i ++ ) {
		a.push_back(i);
	}
	if( (int)a.size() != p ) {
		merge( ops, a, p, a.size() - 1, g );
	}

	print( a, ops );
}/*}}}*/

void solve7( const int n ) {/*{{{*/
	const int k = n / 12;
	const int g = 6 * k + 4;
	vecint a; oplist ops;
	for( int i = 1; i <= k + 1; i ++ ) {
		a.push_back(i);
		a.push_back( 2 * k + 3 - i );
		a.push_back( 8 * k + 7 - 2 * i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 2 * k + 2 + i );
		a.push_back( 4 * k + 4 - i );
		a.push_back( 8 * k + 6 - 2 * i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 6 * k + 5 - 2 * i );
		a.push_back( 9 * k + 7 - i );
		a.push_back( 9 * k + 6 + i );
		update_back(a, ops);
	}
	for( int i = 1; i <= k; i ++ ) {
		a.push_back( 6 * k + 4 - 2 * i );
		a.push_back( 11 * k + 7 - i );
		a.push_back( 11 * k + 7 + i );
		update_back(a, ops);
	}
	{
		a.push_back( 3 * k + 3 );
		a.push_back( 8 * k + 6 );
		a.push_back( 11 * k + 7 );
		update_back(a, ops);
	}
	a.push_back( 6 * k + 4 );

	int p = a.size();
	for( int i = 12 * k + 8; i <= n; i ++ ) {
		a.push_back(i);
	}
	if( (int)a.size() != p ) {
		merge( ops, a, p, a.size() - 1, g );
	}
	print( a, ops );
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "b.in", "r",  stdin );
	freopen( "b.out", "w", stdout );
#endif
	const int n = read<int>();
	const int p = n % 12;
	if( p % 4 == 1 ) 
		solve1(n);
	else if( p % 4 == 0 ) 
		solve4(n);
	else if( p == 3 ) 
		solve3(n);
	else 
		solve7(n);
}
