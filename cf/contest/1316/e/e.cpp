// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/05 00:03:50 
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

inline int full_bit( int cur ) { return ( 1 << cur ) - 1; }

const int N = 1e5 + 1e4;

int n, p, k;
int a[N], int p[N][10];
int f[2][256];

int main() {
	scanf( "%d%d%d", &n, &p, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= p; j ++ ) {
			scanf( "%d", &s[i][j] );
			
		}
	}
	int cur = 0, last = 1;
	for( int o = 1; o <= n; o ++ ) {
		int full_bit_p = full_bit(p);
		for( int i = 0; i <= full_bit_p; i ++ ) {
			f[cur][i] = 0;
		}
		for( int i = 0; i <= full_bit_p; i ++ ) {
			for( int j = 1; j <= p; j ++ ) {
				if( ( i >> ( j - 1 ) ) & 1 ) 
					continue;
			}
		}
	}
}
