// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/24 23:27:01 
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

const int N = 3e5 + 1e4;

int T;
int n, l, k;
int d[N], mx[N];

int main() {
#ifdef woshiluo
	freopen( "b2.in", "r", stdin );
	freopen( "b2.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d", &n, &k, &l );
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &d[i] );
			if( l - d[i] < 0 ) {
				flag = true;
			}
			else {
				mx[i] = l - d[i];
			}
		}
		int up = 0, down = 2 * k;
		for( int i = 1; i <= n; i ++ ) {
			if( k - mx[i] <= 0 )
				up = 0, down = 2 * k;
			else {
				up = Max( up + 1, k - mx[i] );
				down = Min( down + 1, k + mx[i] );
				if( down < up ) 
					flag = true;
			}
		}
		if( flag ) {
			printf( "NO\n" );
		}
		else {
			printf( "YES\n" );
		}
	}
}
