// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-10 22:39
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

const int N = 1100;

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

struct node{ int x = 0, y = 0; };

int T, n;
node a[N];

int main() {
#ifdef woshiluo
	//freopen( "a.in", "r", stdin );
	//freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		bool flag = true;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d%d", &a[i].x, &a[i].y );
			int add_players = a[i].x - a[ i - 1 ].x, add_clears = a[i].y - a[ i - 1 ].y;
			if( add_players < 0 || add_clears < 0 || add_clears > add_players ) {
				flag = false;
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
