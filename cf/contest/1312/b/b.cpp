// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/09 22:40:32 
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

const int N = 110;

int T;
int n;
int a[N];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		for( int i = n; i >= 1; i -- ) {
			printf( "%d ", a[i] );
		}
		printf( "\n" );
	}
}
