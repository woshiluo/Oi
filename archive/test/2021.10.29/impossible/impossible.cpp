/*
 * impossible.cpp
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

std::vector<int> a[2][2];

int main() {
	freopen( "impossible.in", "r", stdin );
	freopen( "impossible.out", "w", stdout );

	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int x, y;
		char op[3];
		scanf( "%s%d%d", op, &x, &y );
		a[ op[0] == 'B' ][(bool)y].push_back(x);
	}
	for( int i = 0; i <= 1; i ++ ) {
		for( int j = 0; j <= 1; j ++ ) {
			std::sort( a[i][j].begin(), a[i][j].end() );
		}
	}
	int res = 0;
	{
		int size1 = a[0][1].size(), size2 = a[1][0].size();
		int p1 = 0, p2 = 0;
		while( p1 < size1 && p2 < size2 ) {
			if( a[0][1][p1] <= a[1][0][p2] ) {
				p1 ++; p2 ++;
				res ++;
			}
			else 
				p2 ++;
		}
	}
	{
		int size1 = a[1][1].size(), size2 = a[0][0].size();
		int p1 = 0, p2 = 0;
		while( p1 < size1 && p2 < size2 ) {
			if( a[1][1][p1] <= a[0][0][p2] ) {
				p1 ++; p2 ++;
				res ++;
			}
			else 
				p2 ++;
		}
	}
	printf( "%d\n", res ) ;

	fclose( stdin );
	fclose( stdout );
	return 0;
}
