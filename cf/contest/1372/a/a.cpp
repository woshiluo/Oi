// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/11 23:05:34 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

std::map<long long,bool> mp;

int t, n;

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		int cur = 1;
		for( int i = 1; i <= n; i ++ ) {
			printf( "1 " );
		}
		printf( "\n" );
	}
}
