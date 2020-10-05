// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/24 22:35:16 
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

const int N = 5e4 + 1e3;
int a[N];

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( i != 1 && a[i] >= a[ i - 1 ] ) {
				flag = true;
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
