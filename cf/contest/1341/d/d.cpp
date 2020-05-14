// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/24 00:16:12 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
T chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
T chk_Min( T &a, T b ) { if( b < a ) a = b; }

int n, k;

int dig[12][8] = { { 1, 1, 1, 0, 1, 1, 1 }, { 0, 0, 1, 0, 0, 1, 0 },
	{ 1, 0, 1, 1, 1, 0, 1 }, { 1, 0, 1, 1, 0, 1, 1 },
	{ 0, 1, 1, 1, 0, 1, 0 }, { 1, 1, 0, 1, 0, 1, 1 },
	{ 1, 1, 0, 1, 1, 1, 1 }, { 1, 0, 1, 0, 0, 1, 0 },
	{ 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0, 1, 1 } };

int ori[2100][10];



int main() {
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 0; j < 7; j ++ ) {
			scanf( "%1d", &ori[i][j] );
		}
	}
	int less = k;
	for( int i = 1; i <= n; i ++ ) {
		bool 
		for( int i = 0; i <= 9; i ++ ) {

		}
	}
}
