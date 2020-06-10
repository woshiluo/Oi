#include <ctime>
#include <cstdio>
#include <cstdlib>

inline int aabs( int a ) { return a < 0? -a: a; }

const int N = 3e6 + 1e2;

int n;
int a[N], b[N];
bool vis[N];
long long ans = (long long)( 1LL << 61LL );

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	srand( time(0) );
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &b[i] );
	}
	int k = (int)(7e7) / n;
	if( k > n ) 
		k = n - 2;
	for( int i = 1; i <= k; i ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			a[i] = -(1e9) + 7;
		}
		int x = ( rand() % n ) + 1;
		int y = x + 2;
		long long res = 0;
		while( y > n || vis[x] ) {
			x = ( rand() % n ) + 1;
			y = x + 2;
		}
		vis[x] = true;
		a[x] = b[x];
		a[y] = b[y];
		a[ x + 1 ] = a[x] + a[y];
		res += aabs( b[ x + 1 ] - a[ x + 1 ] );
		int cur = x - 1;
		while( cur >= 1 ) {
			a[cur] = a[ cur + 1 ] - a[ cur + 2 ];
			res += aabs( b[cur] - a[cur] );
			cur --;
		}
		cur = x + 3;
		while( cur <= n ) {
			a[cur] = a[ cur - 1 ] - a[ cur - 2 ];
			res += aabs( b[cur] - a[cur] );
			cur ++;
		}
		if( res <= ans ) {
			ans = res;
		}
	}
	printf( "%lld\n", ans );
}
