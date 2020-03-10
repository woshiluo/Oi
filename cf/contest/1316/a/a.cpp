// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/04 22:36:53 
#include <cstdio>
#include <cstring>

#include <algorithm>

int t;
int n, m;
int a[1100];

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		int sum = 0;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			sum += a[i];
		}
		m = Min( sum, m );
		printf( "%d\n", m );
	}
}
