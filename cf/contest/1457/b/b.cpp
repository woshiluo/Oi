// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/29 15:18:16 
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

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;
int n, k;

int calc( int col, int a[] ) {
	static int b[N];
	for( int i = 1; i <= n; i ++ ) {
		b[i] = ( a[i] == col );
	}
	int res = 0, less_cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		if( less_cnt != 0 ) 
			less_cnt --;
		else if( b[i] == 0 ) {
			res ++;
			less_cnt = k - 1;
		}
	}
	return res;
}

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int res = INF;
		static int a[N];
		scanf( "%d%d", &n, &k );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		for( int i = 1; i <= 100; i ++ ) {
			chk_Min( res, calc( i, a ) );
		}
		
		printf( "%d\n", res );
	}
}
