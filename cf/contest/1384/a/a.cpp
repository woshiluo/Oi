// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/24 22:43:42 
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
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1100;

int T;
int n;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) { 
		scanf( "%d", &n );
		int mx = 0;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			chk_Max( mx, a[i] );
		}
		char lst[N];
		if( mx == 0 ) 
			mx = 1;
		for( int i = 1; i <= mx; i ++ ) {
			lst[i] = 'a';
		}
		lst[ mx + 1 ] = 0;
		printf( "%s\n", lst + 1 );
		for( int i = 1; i <= n; i ++ ) {
			lst[ a[i] + 1 ] ++;
			if( lst[ a[i] + 1 ] > 'z' ) 
				lst[ a[i] + 1 ] = 'a';
			lst[ mx + 1 ] = 0;
			printf( "%s\n", lst + 1 );
		}
	}
}
