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

#include <map>
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

const int N = 4e5 + 1e3;

std::vector<int> nums;
int a[N], b[N];

int main() {
	int n, k;
	n = read<int>(); k = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		nums.push_back( a[i] );
	}
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	for( int i = 1; i <= n; i ++ ) {
		a[i] = std::lower_bound( nums.begin(), nums.end(), a[i] ) - nums.begin() + 1;
	}

	int res = n + 1;
	std::vector<int> pos( nums.size() + 2, n + 1 );
	const int tot = nums.size();
	for( int i = k + 1; i <= n; i ++ ) {
		chk_Min( pos[ a[i] ], i );
	}
	for( int i = tot; i >= 0; i -- ) 
		chk_Min( pos[i], pos[ i + 1 ] );

	for( int i = 1; i <= k; i ++ ) {
		if( pos[ a[i] + 1 ] == n + 1 )
			continue;
		chk_Min( res, pos[ a[i] + 1 ] - i );
	}

	printf( "%d\n", res == n + 1? -1: res );
}
