// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/14 22:42:47 
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

const int N = 1e5 + 1e4;

int t;
int n;
int a[N];

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		int cnt = 0, la = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( i == 1 || a[i] != la ) {
				la = a[i];
				cnt ++;
			}
		}
		printf( "%d\n", cnt );
	}
}
