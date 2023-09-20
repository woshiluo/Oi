/*
 * d.cpp 2023-08-21
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

struct Portal { int left, rig; };

int get_fa( std::vector<int> &f, cint cur ) {
	if( f[cur] == cur ) 
		return cur;
	return f[cur] = get_fa( f, f[cur] );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();

		std::vector<int> nums, f, queries;
		std::vector<Portal> portals;
		for( int i = 1; i <= n; i ++ ) {
			cint l = read<int>();
			cint r = read<int>();
			cint a = read<int>();
			cint b = read<int>();

			nums.push_back(l);
			nums.push_back(b);
			portals.push_back( { l, b } );
		}

		cint q = read<int>();
		queries.resize(q);
		for( auto &x: queries ) {
			x = read<int>();
			nums.push_back(x);
		}

		std::sort( nums.begin(), nums.end() );
		nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );

		cint size = nums.size();
		f.resize( size + 1 );


		auto find_num = [&nums] ( const int cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; };
		for( auto &portal: portals ) {
			portal.left = find_num( portal.left );
			portal.rig = find_num( portal.rig );
			chk_Max( f[portal.left], portal.rig );
		}
		for( auto &x: queries ) {
			x = find_num(x);
		}

		for( int i = 1; i <= size; i ++ ) {
			chk_Max( f[i], i );
			chk_Max( f[i], f[ i - 1 ] );
		}

		for( auto &pos: queries ) {
			printf( "%d ", nums[ get_fa( f, pos ) - 1 ] );
		}
		printf( "\n" );
	}
}
