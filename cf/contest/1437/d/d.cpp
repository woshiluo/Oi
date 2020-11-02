// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/27 23:57:08 
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		int a[N], son[N];
		memset( son, 0, sizeof(son) );
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		int dep = 1;
		for( int i = 3; i <= n; i ++ ) {
			if( a[i] < a[ i - 1 ] ) {
				if( son[dep - 1] != 0 ) {
					son[dep - 1] --;
					son[dep] ++;
				}
				else 
					dep ++;
			}
			else 
				son[dep] ++;
		}
		printf( "%d\n", dep );
	}
}
