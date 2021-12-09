/*
 *
 * b.cpp
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
	for (; !isdigit(ch); ch = getchar())
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
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int a, b; 
		a = read<int>(); b = read<int>();
		int n = a + b;
		int flow = Min( a, b );

		std::vector<int> ans;
		std::vector<int> res; 
		for( int i = 1; i <= a; i ++ ) res.push_back(0);
		for( int i = 1; i <= b; i ++ ) res.push_back(1);

		{
			// Alice first
			int cur = 0, cnt = 0, less_a = a, less_b = b;
			for( int i = 0; i < n; i ++, cur ^= 1 ) {
				if( !cur ) {
					if( less_a ) {
						less_a --;
						continue;
					}
					else {
						less_b --;
						cnt ++;
					}
				}
				else {
					if( less_b ) {
						less_b --;
						continue;
					}
					else {
						less_a --;
						cnt ++;
					}
				}
			}
			for( int i = 0; i <= flow; i ++ ) {
				if( cnt + i * 2 <= n ) 
					ans.push_back( cnt + i * 2 );
			}
		}
		{
			// Bob first
			int cur = 1, cnt = 0, less_a = a, less_b = b;
			for( int i = 0; i < n; i ++, cur ^= 1 ) {
				if( !cur ) {
					if( less_a ) {
						less_a --;
						continue;
					}
					else {
						less_b --;
						cnt ++;
					}
				}
				else {
					if( less_b ) {
						less_b --;
						continue;
					}
					else {
						less_a --;
						cnt ++;
					}
				}
			}
			for( int i = 0; i <= flow; i ++ ) {
				if( cnt + i * 2 <= n ) 
					ans.push_back( cnt + i * 2 );
			}
		}
		std::sort( ans.begin(), ans.end() );
		ans.erase( std::unique( ans.begin(), ans.end() ), ans.end() );

		printf( "%ld\n", ans.size() );
		for( auto &x: ans ) {
			printf( "%d ", x );
		}
		printf( "\n" );
	}
}
