/*
 * f.cpp
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

#include <random>
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

std::random_device seed;
std::mt19937 rnd(seed());

const int N = 1100;

int base, base1;
int a[N], res[N];

int ans[N];
void gen( cint n ) {
	for( int i = 1; i <= n; i ++ ) {
		ans[i] = ( rnd() % 2 );
	}
}

void get_base( cint n ) {
	for( int i = 1; i <= n; i ++ ) 
		printf( "F" );
	printf( "\n" );
	fflush(stdout);
	base = read<int>();
	if( base == n )
		std::exit(0);
}

void get_base1( cint n ) {
	for( int i = 1; i <= n; i ++ ) 
		printf( "%c", ( i & 1 )? 'T': 'F' );
	printf( "\n" );
	fflush(stdout);
	base1 = read<int>();
	if( base1 == n )
		std::exit(0);
}

int query( cint n, cint p1, cint p2, cint p3 ) {
	for( int i = 1; i <= n; i ++ ) {
		if( i == p1 || i == p2 || i == p3 ) 
			printf( "T" );
		else
			printf( "F" );
	}
	printf( "\n" );
	fflush(stdout);
	int cnt = read<int>();
	if( cnt == n )
		std::exit(0);
	return cnt;
}

int query1( cint n, cint p1, cint p2, cint p3 ) {
	for( int i = 1; i <= n; i ++ ) {
		cint cur = ( i & 1 );
		if( i == p1 || i == p2 || i == p3 ) 
			printf( "%c", ( cur ^ 1 )? 'T': 'F' );
		else
			printf( "%c", ( cur )? 'T': 'F' );
	}
	printf( "\n" );
	fflush(stdout);
	int cnt = read<int>();
	if( cnt == n )
		std::exit(0);
	return cnt;
}

// int tot = 0;
// void get_base( cint n ) {
// 	tot ++;
// 	int cnt = 0;
// 	for( int i = 1; i <= n; i ++ ) 
// 		cnt += ( ans[i] == 0 );
// 	base = cnt;
// }
// void get_base1( cint n ) {
// 	tot ++;
// 	int cnt = 0;
// 	for( int i = 1; i <= n; i ++ ) 
// 		cnt += ( ans[i] == ( i & 1 ) );
// 	base1 = cnt;
// }
// 
// int query( cint n, cint p1, cint p2, cint p3 ) {
// 	tot ++;
// 	int cnt = 0;
// 	for( int i = 1; i <= n; i ++ ) {
// 		if( i == p1 || i == p2 || i == p3 ) 
// 			cnt += ( ans[i] == 1 );
// 		else
// 			cnt += ( ans[i] == 0 );
// 	}
// 	return cnt;
// }
// 
// int query1( cint n, cint p1, cint p2, cint p3 ) {
// 	tot ++;
// 	int cnt = 0;
// 	for( int i = 1; i <= n; i ++ ) {
// 		cint cur = ( i & 1 );
// 		if( i == p1 || i == p2 || i == p3 ) 
// 			cnt += ( ans[i] == ( cur ^ 1 ) );
// 		else
// 			cnt += ( ans[i] == cur  );
// 	}
// 	return cnt;
// }

int main() {
#ifdef woshiluo
//	freopen( "f.in", "r", stdin );
//	freopen( "f.out", "w", stdout );
#endif
	cint n = read<int>();

//	gen(n);
	get_base(n);
	get_base1(n);

	for( int i = 1; i <= n; i ++ ) {
		res[i] = -1;
	}

	for( int i = 1; i + 2 <= n; i += 3 ) {
		cint k1 = query( n, i, i + 1, 0 ) - base;
		if( k1 == 2 || k1 == -2 ) {
			cint k2 = query( n, i + 2, 0, 0 ) - base;
			res[i] = res[ i + 1 ] = ( k1 > 0 );
			res[ i + 2 ] = ( k2 > 0 );
		}
		else {
			cint k2 = query1( n, i, i + 1, i + 2 ) - base1;
			auto chk_pos = []( cint cur ) { return cur & 1; };
			if( k2 == 3 ) {
				res[i] = chk_pos(i) ^ 1;
				res[ i + 1 ] = chk_pos( i + 1 ) ^ 1;
				res[ i + 2 ] = chk_pos( i + 2 ) ^ 1;
			}
			if( k2 == -3 ) {
				res[i] = chk_pos(i);
				res[ i + 1 ] = chk_pos( i + 1 );
				res[ i + 2 ] = chk_pos( i + 2 );
			}
			if( k2 == 1 ) {
				res[i] = chk_pos(i) ^ 1;
				res[ i + 1 ] = chk_pos( i + 1 ) ^ 1;
				res[ i + 2 ] = chk_pos( i + 2 );
			}
			if( k2 == -1 ) {
				res[i] = chk_pos(i);
				res[ i + 1 ] = chk_pos( i + 1 );
				res[ i + 2 ] = chk_pos( i + 2 ) ^ 1;
			}
		}
	}


	for( int i = 1; i <= n; i ++ ) {
		if( res[i] != -1 ) 
			continue;

		int k = query( n, i, 0, 0 );
		if( k > base ) 
			res[i] = 1;
		else 
			res[i] = 0;
	}

	for( int i = 1; i <= n; i ++ ) 
		printf( "%c", res[i]? 'T': 'F' );
	printf( "\n" );

	fflush(stdout);
}
