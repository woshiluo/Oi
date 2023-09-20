/*
 * 1010.cpp
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

template <class T>
T aabs( const T cur ) { return cur < 0? -cur: cur; }

struct Vec {
	int x, y;
	unsigned short kind;

	Vec operator+ ( const Vec &_b ) const { return (Vec){ x + _b.x, y + _b.y, 5 }; }
	Vec operator- ( const Vec &_b ) const { return (Vec){ x - _b.x, y - _b.y, 5 }; }

	ll operator* ( const Vec &_b ) const { return 1LL * x * _b.y - 1LL * _b.x * y; }

	bool operator== ( const Vec &_b ) const { return x == _b.x && y == _b.y; }
};

int main() {
#ifdef woshiluo
	freopen( "1010.in", "r", stdin );
	freopen( "1010.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>();
		cint q = read<int>();

		std::vector<Vec> nodes;
		for( int i = 1; i <= n; i ++ ) {/*{{{*/
			cint x = read<int>();
			cint y = read<int>();

			nodes.push_back( (Vec){ x - 1, y, 0 } );
			nodes.push_back( (Vec){ x + 1, y, 1 } );
			nodes.push_back( (Vec){ x, y - 1, 2 } );
			nodes.push_back( (Vec){ x, y + 1, 3 } );
		}

		std::sort( nodes.begin(), nodes.end(), []( const Vec &_a, const Vec &_b ) { 
			if( _a.x == _b.x ) 
				return _a.y < _b.y;
			return _a.x < _b.x;
		});
		nodes.erase( std::unique( nodes.begin(), nodes.end() ), nodes.end() );/*}}}*/

		std::vector<Vec> shell;
		{/*{{{*/
			{/*{{{*/
				std::vector<Vec> list;
				for( auto &x: nodes ) {
					if( list.size() <= 1 ) {
						list.push_back(x);
						continue;
					}

					while(1) {
						cint size = list.size() - 1;
						if( size < 1 ) 
							break;
						if( ( x - list[size] ) * ( x - list[ size - 1 ] ) <= 0 ) 
							list.pop_back();
						else
							break;
					}

					list.push_back(x);
				}
				for( auto &x: list ) 
					shell.push_back(x);
			}/*}}}*/

			{/*{{{*/
				std::vector<Vec> list;
				for( auto &x: nodes ) {
					if( list.size() <= 1 ) {
						list.push_back(x);
						continue;
					}

					while(1) {
						cint size = list.size() - 1;
						if( size < 1 ) 
							break;
						if( ( x - list[size] ) * ( x - list[ size - 1 ] ) >= 0 ) 
							list.pop_back();
						else
							break;
					}

					list.push_back(x);
				}
				std::reverse( list.begin(), list.end() );
				for( auto &x: list ) 
					shell.push_back(x);
			}/*}}}*/

//			for( auto &x: nodes ) 
//				printf( "%d %d\n", x.x, x.y );
//			printf( "\n" );
//			for( auto &x: shell ) 
//				printf( "%d %d\n", x.x, x.y );
//			printf( "\n\n" );
		}/*}}}*/


		std::reverse( shell.begin(), shell.end() );

		ll a = 0, b = 0, c = 0;
		// ax^2 + bx + c
		cint size = shell.size();
		for( int i = 1; i < size; i ++ ) {
			c += shell[ i - 1 ] * shell[i];
			if( shell[i].kind == shell[ i - 1 ].kind ) {
				if( shell[i].kind <= 1 )
					b += aabs( shell[i].y - shell[ i - 1 ].y ) * 2LL;
				else
					b += aabs( shell[i].x - shell[ i - 1 ].x ) * 2LL;
			}
			else {
				a += 1;
				if( shell[i].kind <= 1 ) {
					cint dx = shell[i].x;
					cint dy = shell[ i - 1 ].y;

					b += aabs( dx - shell[ i - 1 ].x ) + aabs( dy - shell[i].y );
				}
				else {
					cint dx = shell[ i - 1 ].x;
					cint dy = shell[i].y;

					b += aabs( dx - shell[i].x ) + aabs( dy - shell[ i - 1 ].y );
				}
			}
		}

		for( int _ = 1; _ <= q; _ ++ ) {
			cint t = read<int>();
			ll res = a * ( t - 1 ) * ( t - 1 ) + b * ( t - 1 ) + c;

			printf( "%lld.", res >> 1 );
			printf( "%d", ( res & 1LL )? 6: 0 );
			printf( "\n" );
		}
	}
}
