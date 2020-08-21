// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/21 23:02:11 
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T, n;
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int res = 0; bool chance = false;
		int tmp;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &tmp );
			if( tmp == 1 && chance == false ) 
				res ++;
			else 
				chance = true;
		}
		if( chance ) 
			printf( "%s\n", ( res % 2 == 0 )? "First": "Second" );
		else 
			printf( "%s\n", ( res % 2 == 1 )? "First": "Second" );
	}
}
