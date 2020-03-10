// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/04 23:11:43 
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

const int N = 1e6 + 1e5;

int n, m, p;
int a[N], b[N];

int main() {
	scanf( "%d%d%d", &n, &m, &p );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		a[i] %= p;
	}
	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d", &b[i] );
		b[i] %= p;
	}
	int p1 = 0, p2 = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] != 0 ) {
			p1 = i - 1;
			break;
		}
	}
	for( int i = 1; i <= m; i ++ ) {
		if( b[i] != 0 ) {
			p2 = i - 1;
			break;
		}
	}
	printf( "%d\n", p1 + p2 );

}
