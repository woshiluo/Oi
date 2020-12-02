#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1100;
const int INF = 0x3f3f3f3f;

struct node { int time, scr; };

int a[N], f[N];
node b[N];

int main() {
#ifdef woshiluo
	freopen( "luogu.1926.in", "r", stdin );
	freopen( "luogu.1926.out", "w", stdout );
#endif
	int n, m, k, r;
	scanf( "%d%d%d%d", &n, &m, &k, &r );
	for( int i = 1; i <= n; i ++) {
		scanf( "%d", &a[i] );
	}
	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d", &b[i].time );
	}
	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d", &b[i].scr );
	}

	memset( f, INF, sizeof(f) );
	f[0] = 0;
	for( int i = 1; i <= m; i ++ ) {
		for( int j = r; j >= b[i].scr; j -- ) {
			f[j] = std::min( b[i].time + f[ j - b[i].scr ], f[j] );
		}
	}

	int less_time = r - f[k], cnt = 0;
	std::sort( a + 1, a + n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		if( less_time >= a[i] ) {
			less_time -= a[i]; 
			cnt ++;
		}
	}
	
	printf( "%d\n", cnt );
}
