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

const int N = 1100;

char str[N];

int q1cnt = 0;
int query( cint cur ) { 
	printf( "? %d %d\n", 1, cur );
	fflush(stdout);
	static char op[3];
	scanf( "%s", op );
	return op[0] - 'a';
}

int q2cnt = 0;
int query( cint from, cint to ) {
	printf( "? %d %d %d\n", 2, from, to );
	fflush(stdout);
	int res = 0;
	scanf( "%d", &res );
	return res;
}

int a[N], pos[30];
std::vector<int> list;
std::vector<char> chars;

int find( cint left, cint rig, cint ed, cint tot, std::vector<std::pair<int,int>> &ps ) {
	if( left == rig ) 
		return ps[left].second;

	cint len = ( rig - left + 1 );
	cint step = len / 3;
	cint p1 = left + step;

	cint res = query( ps[p1].first, ed );
	if( res == ( tot - p1 + 2 ) ) 
		return find( left, p1 - 1, ed, tot, ps );
	return find( p1, rig, ed, tot, ps );
}

int main() {
	int n = read<int>();
	a[1] = query(1); 
	list.push_back(1);
	chars.push_back( a[1] );
	pos[ a[1] ] = 1;
	
	int lst = 1;
	for( int i = 2; i <= n; i ++ ) {
		int cur = query( lst, i );

		if( cur == 2 ) {
			std::vector<std::pair<int, int>> ps;
			ps.push_back( std::make_pair( -1, -1 ) );
			for( int j = 0; j < 26; j ++ ) 
				if( pos[j] ) 
					ps.push_back( std::make_pair( pos[j], j ) );
			std::sort( ps.begin(), ps.end() );
			std::reverse( ps.begin() + 1, ps.end() );

			cint size = ps.size() - 1;
			int p = 0;
			for( int k = 16; k; k >>= 1 ) {
				if( p + k <= size && query( ps[ p + k ].first, i ) == ( p + k + 1 ) )
					p += k;
			}

			if( p + 1 > size ) 
				a[i] = query(i);
			else
				a[i] = ps[ p + 1 ].second;

			lst = i;
		}
		else
			a[i] = a[ i - 1 ];

		pos[ a[i] ] = i;
	}

	printf( "! " );
	for( int i = 1; i <= n; i ++ ) 
		printf( "%c", a[i] + 'a' );

	fflush(stdout);
}
