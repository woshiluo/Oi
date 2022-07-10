/*
 * b.cpp
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

const int N = 2e5 + 1e4;

std::vector<int> sum[30];
std::vector<int> pos[30];

bool work() {
	for( int j = 0; j < 26; j ++ ) {
		cint size = pos[j].size();
		for( int i = 0; i < size; i ++ ) {
			for( int k = 0; k < 26; k ++ ) {
				if( k == j ) 
					continue;
				if( pos[k].size() == 0 )
					continue;
				if( i - 1 >= 0 && sum[k][ pos[j][i] ] - sum[k][ pos[j][ i - 1 ] - 1 ] == 0  ) 
					return false;
				if( i - 2 >= 0 && sum[k][ pos[j][i] ] - sum[k][ pos[j][ i - 2 ] - 1 ] <= 1  ) 
					return false;
			}
		}
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		static char str[N];
		static int a[N];
		scanf( "%s", str + 1 );
		cint n = strlen( str + 1 );
		for( int i = 0; i < 26; i ++ ) {
			sum[i].resize(0);
			sum[i].resize( n + 5, 0 );
			pos[i].resize(0);
		}
		for( int i = 1; i <= n; i ++ ) {
			a[i] = str[i] - 'a';
			pos[ a[i] ].push_back(i);
			sum[ a[i] ][i] = 1;
		}
		for( int j = 0; j < 26; j ++ ) {
			for( int i = 1; i <= n; i ++ ) {
				sum[j][i] += sum[j][ i - 1 ];
			}
		}
		printf( "%s\n", work()? "Yes": "No" );
	}
}
