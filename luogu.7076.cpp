#include <cstdio>

#include <algorithm>

typedef unsigned long long ull;

const int N = 1e6 + 1e5;

struct node { int pos, val; };

bool cmp( node _a, node _b ) { return _a.val < _b.val; }

int n, m, c, k;
int pos[N], in_degree[N];
node a[N];
bool vis[N], used[N];

void mark_vis( ull cur ) {
	ull res = 1; int cnt = 0;
	while( cnt < k && cnt < 64 ) {
		if( cur & res ) 
			vis[cnt] = true;
		cnt ++;
		res <<= 1;
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.7076.in", "r", stdin );
	freopen( "luogu.7076.out", "w", stdout );
#endif
	scanf( "%d%d%d%d", &n, &m, &c, &k );
	for( int i = 1; i <= n; i ++ ) {
		ull tmp;
		scanf( "%llu", &tmp );
		mark_vis(tmp);
	}

	for( int i = 1; i <= m; i ++ ) {
		scanf( "%d%d", &a[i].pos, &a[i].val );
	}

	std::sort( a + 1, a + m + 1, cmp );
	int tot = 0;
	for( int i = 1; i <= m; i ++ ) {
		if( i == 1 || a[i].val != a[ i - 1 ].val ) 
			tot ++;
		a[i].val = tot;
		in_degree[ a[i].pos ] ++;
		if( vis[ a[i].pos ] )
			used[ a[i].val ] = true;
	}

	for( int i = 1; i <= m; i ++ ) {
		if( used[ a[i].val ] ) 
			in_degree[ a[i].pos ] --;
	}
	
	int cnt = 0;
	for( int i = 0; i < k; i ++ ) {
		cnt += ( in_degree[i] == 0 );
	}
	
	if( cnt == 64 ) {
		if( n == 0 ) {
			printf( "18446744073709551616" );
			return 0;
		}
		else {
			n --;
			ull res = 18446744073709551615ULL;
			printf( "%llu\n", res - n );
			return 0;
		}
	}

	printf( "%llu\n", ( 1ull << cnt ) - n );
}
