#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 1e6 + 1e5;

int _case;
int n, m, k;
long long ans;

struct ask {
	int left, rig;
} a[N];

// BIT Tree 
int BIT[N];
inline int lowbit( int cur ) { return cur & ( - cur ); }
void add( int pos, int val ) { 
	for( ; pos <= m; pos += lowbit(pos) )
		BIT[pos] += val;
}
int query( int pos ) {
	int res = 0;
	for( ; pos; pos -= lowbit(pos) ) 
		res += BIT[pos];
	return res;
}
// BIT End

bool cmp( ask a, ask b ) { 
	if( a.left == b.left ) 
		return a.rig < b.rig;
	return a.left < b.left; 
}

void init() {
	memset( BIT, 0, sizeof(BIT) );
	ans = 0;
}

void readin() {
	scanf( "%d%d%d", &n, &m, &k );
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d%d", &a[i].left, &a[i].rig );
	}
	std::sort( a + 1, a + k + 1, cmp );
}

void work() {
	for( int i = 1; i <= k; i ++ ) {
		add( a[i].rig, 1 );
		ans += query( m ) - query( a[i].rig );
	}
}


int main() {
#ifdef woshiluo
	freopen( "poj.3067.in", "r", stdin );
	freopen( "poj.3067.out", "w", stdout );
#endif
	scanf( "%d", &_case );
	for( int i = 1; i <= _case; i ++ ) {
		init();
		readin();
		work();
		printf( "Test case %d: %lld\n", i, ans );
	}
}
