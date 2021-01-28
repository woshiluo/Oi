// Woshiluo<woshiluo@woshiluo.site>
// 2020/12/18 00:11:22 
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

const int N = 4e5 + 1e4;

int T;

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	scanf( "%d", &T );
	while( T -- ) {
		int n;
		static int a[N], sum[N], re_sum[N];
		static int avil[N], re_avil[N];
		static bool vis[N];
		memset( vis, 0, sizeof(vis) );
		memset( avil, 0, sizeof(avil) ); 
		memset( re_avil, 0, sizeof(re_avil) ); 
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			vis[ a[i] ] = true;
		}

		 n <<= 1;
		 int cur = 0;
		 for( int i = 0; i <= n; i ++ ) {
			 if( vis[i] ) 
				 cur ++;
			 else if( cur > 0 )
				 cur --;
			 sum[i] = cur;
			 if( i != 0 )
				 avil[i] = avil[ i - 1 ] + ( !vis[i] );
		 }
		 cur = 0;
		 for( int i = n; i >= 0; i -- ) {
			 if( vis[i] ) 
				 cur ++;
			 else if( cur > 0 )
				 cur --;
			 re_sum[i] = cur;
			 re_avil[i] = re_avil[ i + 1 ] + ( !vis[i] );
		 }
		 sum[ n + 1 ] = sum[n]; re_sum[ n + 1 ] = 0;

		 int ans = 0;
		 n >>= 1;
		 for( int i = 0; i <= n; i ++ ) {
			 int pos = a[i];
			 if( sum[pos] <= re_avil[ pos + 1 ] && re_sum[ pos + 1 ] <= avil[pos] )
				 ans ++;
		 }

		 printf( "%d\n" ,ans );
	}

	return 0;
}
