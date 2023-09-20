/*
 * luogu.1563.cpp 2023-08-13
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
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

const int S = 15;

struct Person {
	bool status;
	char name[S];
};

int main() {
#ifdef woshiluo
	freopen( "luogu.1563.in", "r", stdin );
	freopen( "luogu.1563.out", "w", stdout );
#endif

	cint n = read<int>();
	cint m = read<int>();

	std::vector<Person> persons(n);
	for( auto &person: persons ) {
		person.status = read<int>();
		scanf( "%s", person.name );
	}

	int cur = 0;
	for( int i = 1; i <= m; i ++ ) {
		cint status = read<int>() ^ persons[cur].status;
		cint step = read<int>();

		cur += step * ( status? 1: -1 );
		cur = ( ( cur % n ) + n ) % n;
	}

	printf( "%s\n", persons[cur].name );
}
