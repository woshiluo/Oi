/*
 * unlock.cpp
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

#include <map>
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

const int N = 2e6 + 1e5;

int f[N];
std::map<int, std::map<int, bool>> mp;

int main() {
	freopen( "unlock.in", "r", stdin );
	freopen( "unlock.out", "w", stdout );
	int n, m;
	n = read<int>(); m = read<int>();
	int q = read<int>();
	while( q -- ) {
		int x, y;
		x = read<int>(); y = read<int>();
		mp[x][y] = true;
	}
	int ans = 0;
	f[1] = 1;
	while( f[n] != m ) {
		for( int i = n; i > 0; i -- ) { 
			if( f[i] ) {
				int g = f[i] + i;
				if( mp[i][ f[i] ] ) 
					g ++;
				int gx = Min( g, n );
				int gy = Min( g, m );
				chk_Max( f[gx], f[i] );
				f[i] = gy;
			}
		}
		ans ++;
	}
	printf( "%d\n", ans );
	fclose( stdin );
	fclose( stdout );
	return 0;
}
