// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/19 22:35:39 
#include <cstdio>
#include <cstring>

#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

int T, n;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		if( n == 1 ) {
			printf( "-1\n" );
			continue;
		}
		printf( "2" );
		for( int i = 1; i < n; i ++ ) 
			printf( "3" );
		printf( "\n" );
	}
}
