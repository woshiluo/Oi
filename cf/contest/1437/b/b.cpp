// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/27 22:46:49 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		int la = -1, cnt = 0, fir;
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%1d", &tmp );
			if( la == -1 ) {
				fir = tmp;
				la = tmp;
				continue;
			}
			if( la == ( fir ^ 1 ) )
				cnt += ( la == tmp );
			la = tmp;
		}
		printf( "%d\n", cnt == 0? 0: cnt );
	}
}
