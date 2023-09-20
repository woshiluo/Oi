/*
 * a.cpp
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

template<class T>/*{{{*/
T Min( T a, T b ) { return a < b? a: b; }
template<class T>
T Max( T a, T b ) { return a > b? a: b; }
template<class T>
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T>
void chk_Max( T &a, T b ) { if( a < b ) a = b; }
template<class T>
T aabs( T a ) { return a < 0? -a: a; }

bool is_digit( char cur ) { return cur >= '0' && cur <= '9'; }
template<class T>
T read() { 
	char x = getchar(); T res = 0, k = 1;
	for( ; !is_digit(x); x = getchar() ) 
		if( x == '-' ) 
			k = -1;
	for( ; is_digit(x); x = getchar() )
		res = res * 10 + ( x - '0' );
	return res * k;
}/*}}}*/

struct Node {
	int x, y;

	bool operator< ( const Node &b ) const { return x < b.x && y < b.y; }

	int check( const Node &b ) const { return Min( aabs( x - b.x ), aabs( y - b.y ) ); }
};

void calc() {
	int m, n;
	Node node[N];
	std::vector<int> numbers;
	m = read<int>(); n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		node[i].x = read<int>(); node[i].y = read<int>();
		numbers.push_back( node[i].x );
		numbers.push_back( node[i].y );
	}
	std::sort( numbers.begin(), numbers.end() );
	numbers.erase( std::unique( numbers.begin(), numbers.end() ), numbers.end() );
	auto get_x = [numbers]( int cur ) { return std::lower_bound( numbers.begin(), numbers.end(), cur ) - numbers.begin() + 1; };
	for( int i = 1; i <= n; i ++ ) {
		node[i].x = get_x( node[i].x );
		node[i].y = get_x( node[i].y );
	}
}

int main() {
	int T = read<int>();
	while( T -- ) {
		calc();
	}
}
