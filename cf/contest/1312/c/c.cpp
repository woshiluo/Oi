// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/09 22:58:45 
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
long long k;
bool vis[N];
long long a[N];

inline void wrong() {
	printf( "NO\n" );
}

inline void right() {
	printf( "YES\n" );
}

void calc() {
	for( int i = 1; i <= n; i ++ ) {
		if( a[i] == 0 ) {
			continue;
		}
		long long cur = a[i];
		int cnt = 1;
		while( cur ) {
			int tmp = cur % k;
			if( tmp > 1 ) {
				wrong();
				return ;
			}
			if( tmp == 1 ) {
				if( vis[cnt] == false ) 
					vis[cnt] = true;
				else {
					wrong();
					return ;
				}
			}
			cur /= k;
			cnt ++;
		}
	}
	right();
}

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		memset( vis, 0, sizeof(vis) );

		scanf( "%d%lld", &n, &k );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%lld", &a[i] );
		}
	
		calc();
	}
}
