// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/19 22:35:42 
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

const int N = 2e5 + 1e4;

int n;
int b[N];
long long a[N];

int main() {
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
	}
	long long cur_max = 0;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = cur_max + b[i];
		chk_Max( cur_max, a[i] );
	}
	
	for( int i = 1; i <= n; i ++ ) {
		printf( "%lld ", a[i] );
	}
}
