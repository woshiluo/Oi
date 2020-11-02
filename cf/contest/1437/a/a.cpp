// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/27 22:35:40 
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
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int l, r;
		scanf( "%d%d", &l, &r );
		if( ( r - l + 1 ) <= l )
			printf( "YES\n" );
		else 
			printf( "NO\n" );
	}
}
