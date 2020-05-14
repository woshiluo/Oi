// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/23 23:12:09 
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
T chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
T chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 2e5 + 1e4;

int T;
int n, k;
int a[N], sum[N];


int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T --  ) {
		int ans = 0, ans_l = 1;
		scanf( "%d%d", &n, &k );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			sum[i] = 0;
		}
		for( int i = 2; i < n; i ++ ) {
			if( a[ i - 1 ] < a[i] && a[i] > a[ i + 1 ] ) 
				sum[i] ++;
			sum[i] += sum[ i - 1 ];
		}
		for( int left = 1, rig = k; rig <= n; left ++, rig ++ ) {
			int res = sum[ rig - 1 ] - sum[left];
			if( res > ans ) {
				ans = res;
				ans_l = left;
			}
		}
		printf( "%d %d\n", ans + 1, ans_l );
	}
}
