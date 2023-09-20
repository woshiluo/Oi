#include <cstdio>

const int N = 1e5 + 1e4;

int n, k;
int a[N], pool[N];

inline int chk( int cur ) { return ( cur & 1 )? -1: 1; }

int main() {
#ifdef woshiluo
	freopen( "luogu.6294.in", "r", stdin );
	freopen( "luogu.6294.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}
	while( k -- ) {
		int p;
		scanf( "%d", &p );
		for( int i = 1; i < p; i ++ ) {
			pool[ a[i] ] ++;
		}
		int mx = n;
		long long ans = 0;
		for( int i = 0; i < n; i ++ ) {
			int cur = p + i;
			if( cur <= n ) {
				if( a[cur] >= mx ) {
					ans += chk(i) * a[cur];
					continue;
				}
				else 
					pool[ a[cur] ] ++;
			}
			while( pool[mx] == 0 ) 
				mx --;
			ans += chk(i) * mx;
			pool[mx] --;
		}
		printf( "%lld\n", ans );
	}
}
