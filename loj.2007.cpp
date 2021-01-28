#include <cstdio>

#include <queue>
#include <algorithm>

const int N = 2e5 + 1e4;
const int K = 20;

int n, m;

struct node {
	int left, rig, id;
} a[N << 1];

bool cmp( node a, node b ) { 
	if( a.left == b.left ) 
		return a.rig < b.rig;
	return a.left < b.left;
}

int f[ N << 1 ][K], ans[N];

int main() {
#ifdef woshiluo
	freopen( "loj.2007.in", "r", stdin );
	freopen( "loj.2007.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].left, &a[i].rig );
		if( a[i].rig < a[i].left ) 
			a[i].rig += m;
		a[ i + n ] = (node) { a[i].left + m, a[i].rig > m? m + m + 1: a[i].rig + m, 0 };
	}
	int tot_n = n + n;
	for( int i = 1; i <= tot_n; i ++ ) {
		a[i].id = i;
	}
	std::sort( a + 1, a + n + n + 1, cmp );

	int p = 1;
	for( int i = 1; i <= tot_n; i ++ ) {
		while( a[p].left <= a[i].rig && p <= tot_n ) {
			p ++;
		}
		if( p - 1 != i )
			f[i][0] = p - 1;
	}

	for( int k = 1; k < K; k ++ ) {
		for( int i = 1; i <= tot_n; i ++ ) {
			f[i][k] = f[ f[i][ k - 1 ] ][ k - 1 ];
		}
	}

	for( int i = 1; i <= tot_n; i ++ ) {
		if( a[i].id > n ) 
			continue;
		int st = a[i].left;
		int ed = st + m - 1;
		int cur = i;
		for( int k = K - 1; k >= 0; k -- ){
			if( f[cur][k] && a[f[cur][k]].rig <= ed ) {
				ans[ a[i].id ] += ( 1 << k );
				cur = f[cur][k];
			}
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		printf( "%d ", ans[i] + 2 );
	}
}
