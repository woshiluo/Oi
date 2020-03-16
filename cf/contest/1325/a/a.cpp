// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/14 22:36:48 

#include <cmath>
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

int t, x;

int main() {
	scanf( "%d", &t );
	while( t -- ) {
		scanf( "%d", &x );
		int sq = std::sqrt(x) + 1;
		for( int i = 1; i <= sq; i ++ ) {
			if( x % i == 0 ) {
				int tmp = ( x / i ) - 1;
				if( tmp == 0 ) 
					continue;
				printf( "%d %d\n", i, tmp * i );
				break;
			}
		}
	}
}
