// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/04 22:41:26 
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

int t, n;
char s[5100], tmp[5100], lowest[5100];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		int lowest_k = 1;
		scanf( "%d", &n );
		scanf( "%s", s + 1 );
		for( int i = 1; i <= n; i ++ ) {
			lowest[i] = s[i];
		}
		for( int k = 2; k <= n; k ++ ) {
			int less = n - k + 2;
			for( int i = 1; i < k; i ++ ) {
				tmp[ less + i - 1 ] = s[i];
			}
			if( ( k & 1 ) == ( n & 1 ) ) {
				for( int i = 1; i < k; i ++ ) {
					tmp[ less + i - 1 ] = s[ ( k - 1 ) - i + 1 ];
				}
			}
			for( int i = 1; i < less; i ++ ) {
				tmp[i] = s[ k + i - 1 ];
			}
//			printf( "%d %s\n", k, tmp + 1 );
			for( int i = 1; i <= n; i ++ ) {
				if( tmp[i] < lowest[i] ) {
					lowest_k = k;
					for( int j = 1; j <= n; j ++ ) {
						lowest[j] = tmp[j];
					}
					break;
				}
				else if( tmp[i] != lowest[i] )
					break;
			}
		}
		lowest[ n + 1 ] = 0;
		printf( "%s\n%d\n", lowest + 1, lowest_k );
	}
}
