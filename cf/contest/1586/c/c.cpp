/*
 * c.cpp
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

const int N = 1e6 + 1e5;

int sum[N];
bool right[N];

std::vector<bool> mp[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n, m;
	n = read<int>(); m = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		static char str[N];
		scanf( "%s", str + 1 );
		mp[i].push_back(0);
		for( int j = 1; j <= m; j ++ ) 
			mp[i].push_back( ( str[j] == 'X' ) );
	}
	for( int j = 2; j <= m; j ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			if( i != 1 ) {
				if( mp[ i - 1 ][j] && mp[i][ j - 1 ] )
					right[j] = true;
			}
		}
	}
	for( int i = 1; i <= m; i ++ )
		sum[i] = sum[ i - 1 ] + right[i];
	int q = read<int>();
	while( q -- ) {
		int left, rig;
		left = read<int>(); rig = read<int>();
		if( sum[rig] - sum[left] != 0 )
			printf( "NO\n" );
		else
			printf( "YES\n" );
	}
}
