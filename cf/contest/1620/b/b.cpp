/*
 * b.cpp
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int a, b; ll res = 0;
		std::vector<int> h[2], v[2];
		a = read<int>(); b = read<int>();
		auto read_side = []( std::vector<int> &list ) { 
			int k = read<int>();
			while( k -- ) 
				list.push_back( read<int>() );
			std::sort( list.begin(), list.end() );
		};
		read_side( h[0] ); read_side( h[1] );
		read_side( v[0] ); read_side( v[1] );
		auto check = [&res]( int cur, std::vector<int> same[], std::vector<int> other[], int k ) {
			if( same[cur].size() < 2 ) 
				return ;
			int len = same[cur].back() - same[cur][0];
			if( same[cur^1].size() ) 
				chk_Max( res, 1LL * len * k );
			else {
				if( other[0].size() )
					chk_Max( res, 1LL * len * other[0].back() );
				if( other[1].size() )
					chk_Max( res, 1LL * len * other[1].back() );
			}
		};

		check( 0, h, v, b ); check( 1, h, v, b );
		check( 0, v, h, a ); check( 1, v, h, a );
		printf( "%lld\n", res );
	}
}
