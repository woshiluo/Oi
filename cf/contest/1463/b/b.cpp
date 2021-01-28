// Woshiluo<woshiluo@woshiluo.site>
// 2020/12/17 23:09:39 
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

inline int get_limit( int cur ) {
	int res = 1;
	while( res <= cur ) {
		if( ( res << 1 ) > cur )
			return res;
		res <<= 1;
	}
	return res;
}

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			printf( "%d ", get_limit(tmp) );
		}
		printf( "\n" );
	}
}
