// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/21 22:41:11 
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

const int N = 11000;

int T;
int a, b;
bool ta[N];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &a, &b );
		memset( ta, 0, sizeof(ta) );
		for( int i = 1; i <= a; i ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			ta[tmp] = 1;
		}
		int res = 0;
		for( int j = 1; j <= b; j ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			if( ta[tmp] ) {
				res = tmp;
			}
		}
		if( res == 0 )
			printf( "NO\n" );
		else {
			printf( "YES\n%d %d\n", 1, res );
		}
	}
}
