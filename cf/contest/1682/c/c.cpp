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

#include <map>
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
const int INF = 0x3f3f3f3f;

int a[N];
int f[N][2][2];
// 0/1 crossed
// 0/1 wait for

int main() {
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		std::map<int, int> pool;
		std::vector<int> cnt;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			pool[ a[i] ] ++;
		}
		cnt.push_back(0);
		for( auto &pair: pool ) {
			cnt.push_back( pair.second >= 2? 2: 1 );
		}
		f[0][0][0] = 0;
		f[0][0][1] = f[0][1][0] = f[0][1][1] = -INF;

		cint size = cnt.size() - 1;
		for( int i = 1; i <= size; i ++) {
			f[i][0][0] = f[ i - 1 ][0][0];
			f[i][0][1] = f[ i - 1 ][0][1];
			f[i][1][0] = f[ i - 1 ][1][0];
			f[i][1][1] = f[ i - 1 ][1][1];

			chk_Max( f[i][0][0], f[ i - 1 ][0][1] + 1 );

			chk_Max( f[i][0][1], f[ i - 1 ][0][0] );

			chk_Max( f[i][1][0], f[ i - 1 ][1][1] + 1 );

			chk_Max( f[i][1][1], f[ i - 1 ][1][0] );

			chk_Max( f[i][1][0], f[ i - 1 ][0][0] + 1 );
			chk_Max( f[i][1][1], f[ i - 1 ][0][1] + 1 );

			if( cnt[i] != 1 ) {
				chk_Max( f[i][0][0], f[ i - 1 ][0][0] + 1 );

				chk_Max( f[i][0][1], f[ i - 1 ][0][1] + 1 );

				chk_Max( f[i][1][0], f[ i - 1 ][1][0] + 1 );

				chk_Max( f[i][1][1], f[ i - 1 ][1][1] + 1 );
			}
		}
		printf( "%d\n", Max( Max( f[size][0][0], f[size][0][1] ), Max( f[size][1][0], f[size][1][1] ) ) );
	}
}
