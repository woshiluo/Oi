// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/02 23:25:30 
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

const int N = 3e5 + 1e3;

int T;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		int a[N];
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) 
			scanf( "%d", &a[i] );
		bool flag = true;
		int l = a[1], r = 0;
		for( int i = 2; i <= n; i ++ ) {
			if( r > a[i] ) {
				flag = false;
				break;
			}
			if( l + r <= a[i] ) 
				r = a[i] - l;
			else
				l = a[i] - r;
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
