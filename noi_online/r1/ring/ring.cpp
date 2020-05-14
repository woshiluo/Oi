#include <cstdio>

#include <algorithm>

const int N = 2e5 + 1e4;

int n, m;
int a[N], b[N];

inline int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

struct node {
	int left, rig, val;
	bool vis;
	node( int _val = 0 ) {
		left = rig = vis = 0;
		val = _val;
	}
} e[N];
int ecnt;

inline long long calc( int l, int r ) {
	int left_p, rig_p;
	long long res = 0;
	bool left = 1;
	ecnt = 0;
	ecnt ++;
	e[ecnt] = node( a[r] );
	left_p = rig_p = 1;
	for( int i = r - 1; i > l; i -- ) {
		ecnt ++;
		e[ecnt] = node( a[i] );
		if( left ) {
			e[ecnt].rig = left_p;
			e[left_p].left = ecnt;
			left_p = ecnt;
		}
		else {
			e[ecnt].left = rig_p;
			e[rig_p].rig = ecnt;
			rig_p = ecnt;
		}
		left = ( left == 0 );
	}
	int tmp = 1;
	while( e[tmp].left ) {
		res += 1LL * e[tmp].val * e[ e[tmp].left ].val;
		tmp = e[tmp].left;
	}
	tmp = 1;
	while( e[tmp].rig ) {
		res += 1LL * e[tmp].val * e[ e[tmp].rig ].val;
		tmp = e[tmp].rig;
	}

	if( left_p != rig_p )
		res += 1LL * e[left_p].val * a[l] + 1LL * e[rig_p].val * a[l];
	else 
		res += 1LL * e[left_p].val * a[l];
	
	if( r - l + 1 == 2 ) 
		return res * 2;
	return res;
}

int main() {
	freopen( "ring.in", "r", stdin );
	freopen( "ring.out", "w", stdout );

	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	} 
	
	std::sort( a + 1, a + n + 1 );
	while( m -- ) {
		long long ans = 0;
		int k;
		scanf( "%d", &k );
		int sql = gcd( n, k );
		int sql_len = n / sql;
		for( int i = 1; i <= sql; i ++ ) {
			ans += calc( ( i - 1 ) * sql_len + 1, 
					i * sql_len );
		}
		printf( "%lld\n", ans );
	}
}
