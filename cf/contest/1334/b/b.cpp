// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020-04-10 23:08
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

const int N = 1e5 + 1e4;

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

int T;
int n, x;
int a[N];

int main() {
	//freopen( "b.in", "r", stdin );
	//freopen( "b.out", "w", stdout );
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &n, &x );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		int cnt = 0;
		long long sum = 0;
		for( int i = n; i >= 1; i --  ){
			sum += a[i]; cnt ++;
			if( ( sum / cnt ) >= x )  
				continue;
			else {
				cnt --;
				break;
			}
		}
		printf( "%d\n", cnt );
	}
}
