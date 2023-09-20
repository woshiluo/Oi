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

#include <vector>
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

const int N = 2e5 + 1e4;

struct Seg { int l, r; };

int a[N], b[N];

template <class T>
T aabs( T cur ) { return cur < 0? -cur: cur; }

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%1d", &a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%1d", &b[i] );
		}

		std::vector<Seg> sega,segb;
		{/*{{{*/
			int la = -1;
			for( int i = 1; i <= n; i ++ ) {
				if( a[i] ) {
					if( la == -1 )
						la = i;
				}
				else {
					if( la != -1 ) {
						sega.push_back( (Seg) { la, i - 1 } );
						la = -1;
					}
				}
			}
			if( la != -1 ) {
				sega.push_back( (Seg) { la, n } );
				la = -1;
			}
		}/*}}}*/

		{/*{{{*/
			int la = -1;
			for( int i = 1; i <= n; i ++ ) {
				if( b[i] ) {
					if( la == -1 )
						la = i;
				}
				else {
					if( la != -1 ) {
						segb.push_back( (Seg) { la, i - 1 } );
						la = -1;
					}
				}
			}
			if( la != -1 ) {
				segb.push_back( (Seg) { la, n } );
				la = -1;
			}
		}/*}}}*/

		if( sega.size() != segb.size() ) {
			printf( "-1\n" );
			continue;
		}

		bool flag = true;
		cint size = sega.size();
		ll res = 0;
		for( int i = 0; i < size; i ++ ) {
			auto pa = sega[i];
			auto pb = segb[i];
			if( pa.l == 1 && pb.l != 1 ) 
				flag = false;
			if( pa.l != 1 && pb.l == 1 ) 
				flag = false;
			if( pa.r == n && pb.r != n ) 
				flag = false;
			if( pa.r != n && pb.r == n ) 
				flag = false;
			res += aabs( pa.l - pb.l ) + aabs( pa.r - pb.r );
		}

		if( !flag ) 
			printf( "-1\n" );
		else
			printf( "%lld\n", res );

	}
}
