/*
 * a.cpp
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
	int h, w;
	h = read<int>(); w = read<int>();
	std::vector<std::vector<int>> mp( h + 1, std::vector<int>(w + 1) );
	{
		std::vector<std::vector<int>> tmp( h + 1, std::vector<int>(w + 1) );
		for( int i = 1; i <= h; i ++ ) {
			for( int j = 1; j <= w; j ++ ) {
				tmp[i][j] = read<int>();
			}
		}
		for( int i = 1; i <= h; i ++ ) {
			for( int j = 1; j <= w; j ++ ) {
				if( h < w ) 
					mp[j][i] = tmp[i][j];
				else
					mp[i][j] = tmp[i][j];
			}
		}
		if( h < w ) 
			std::swap( h, w );
	}

	std::vector<std::vector<int>> f( w + 1 ), g( w + 1 );
	for( int i = 1; i <= h; i ++ ) {
		for( int j = 1; j <= w; j ++ )  {
			if( mp[i][j] < mp[i][ j - 1 ] ) 
				f[i].push_back(j);
		}
		for( int j = w; j >= 1; j -- ) {
			if( mp[i][j] < mp[i][ j + 1 ] ) 
				g[i].push_back(j);
		}
		std::sort( f.begin(), f.end() );
		std::sort( g.begin(), g.end() );
	}
	for( int j = 1; j 
}
