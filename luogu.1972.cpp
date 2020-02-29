#include <cstdio>

#include <algorithm>

inline int in() {
	int res = 0; char x = getchar();
	while( x < '0' || x > '9' )
		x = getchar();
	while( x >= '0' && x <= '9' ) {
		res = ( res * 10 ) + x - '0';
		x = getchar();
	}
	return res;
}

const int N = 1e6 + 1e5;

struct _ask {
	int id, left, rig;
} ask[N];

int n, m, a[N], ans[N], la[N];

// BIT Start
int BIT[N];
inline int lowbit( int cur ) { return cur & ( - cur ); }
void add( int pos, int val ) {
	for( ; pos <= n; pos += lowbit(pos) )
		BIT[pos] += val;
}
int sum( int pos ) {
	int res = 0;
	for( ; pos; pos -= lowbit(pos) ) {
		res += BIT[pos];
	}
	return res;
}

inline int query( int left, int rig ) {
	return sum(rig) - sum( left - 1 );
}
// BIT End

bool cmp( _ask _a, _ask _b ) {
	return _a.rig < _b.rig;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1972.in", "r", stdin );
	freopen( "luogu.1972.out", "w", stdout );
#endif
	n = in();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = in();
	}

	m = in();
	for( int i = 1; i <= m; i ++ ) {
		ask[i].left = in(); ask[i].rig = in();
		ask[i].id = i;
	}
	std::sort( ask + 1, ask + m + 1, cmp );

	int p1 = 1;
	for( int i = 1; i <= m; i ++ ) {
		while( p1 <= ask[i].rig ) {
			if( la[ a[p1] ] != 0 ) {
				add( la[ a[p1] ], -1 );
			}
			add( p1, 1 );
			la[ a[p1] ] = p1;
			p1 ++;
		}
		ans[ ask[i].id ] = query( ask[i].left, ask[i].rig );
	}

	for( int i = 1; i <= m; i ++ ) {
		printf( "%d\n", ans[i] );
	}
}
