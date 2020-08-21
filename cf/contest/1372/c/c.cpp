// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/11 23:47:27 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

const int N = 2e5 + 1e4;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int t;
int n;
int a[N];

int main() {
	scanf( "%d", &t );
	while( t --  ) {
		scanf( "%d", &n );
		int cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( i != 1 ) {
				if( a[i] < a[ i - 1 ] )
					cnt ++;
			}
		}
		printf( "%d\n", cnt );
	}
}
