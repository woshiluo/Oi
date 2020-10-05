// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/24 22:45:51 
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

int get_max( int x ) {
	int p1 = 0;
	while( x ) {
		if( ( x >> 1 ) == 0 ) 
			return p1;
		p1 ++;
		x >>= 1;
	}
	return 0;
}

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
		int sum[40];
		long long cnt = 0;
		memset( sum, 0, sizeof(sum) );
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			tmp = get_max(tmp);
			for( int i = 0; i < 32; i ++ ) {
				if( i == tmp ) 
					continue;
				cnt += sum[i];
			}
			sum[tmp] ++;
		}
		printf( "%lld\n", ( 1LL * n * ( n - 1 ) ) / 2LL - cnt );
	}
}
