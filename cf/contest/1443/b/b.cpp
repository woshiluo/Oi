// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/02 22:41:27 
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

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

int T;

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		int a, b;
		char str[N];
		int f[N][2];
		memset( f, INF, sizeof(f) );

		scanf( "%d%d", &a, &b );
		scanf( "%s", str + 1 );
		int n = strlen( str + 1 );

		f[0][0] = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( str[i] == '1' ) {
				chk_Min( f[i][1], f[ i - 1 ][0] + a );
				chk_Min( f[i][1], f[ i - 1 ][1] );
			}
			else {
				chk_Min( f[i][0], f[ i - 1 ][0] );
				chk_Min( f[i][0], f[ i - 1 ][1] );
				chk_Min( f[i][1], f[ i - 1 ][0] + b + a );
				chk_Min( f[i][1], f[ i - 1 ][1] + b );
			}
		}
		
		printf( "%d\n", Min( f[n][0], f[n][1] ) );
	}
}
