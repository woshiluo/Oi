#include <cstdio>

#include <queue>
#include <algorithm>

const int N = 1e5 + 1e4;
const int INF = 0x3f3f3f3f;

int n;
int a[N], b[N], c[N], p[N];
int in[N], out[N];

struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	out[cur] ++; in[to] ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}

int query( int left, int rig, int val ) {
	while( left <= rig ) {
		int mid = ( left + rig ) >> 1;
		if( p[mid] < val ) 
			left = mid + 1;
		else
			rig = mid - 1;
	}
	return left - 1;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.3971.in", "r", stdin );
	freopen( "luogu.3971.out", "w", stdout );
#endif
	scanf( "%d", &n );
	int la[N];
	for( int i = 0; i <= n; i ++ ) {
		la[i] = -1;
	}
	for( int i = 1; i <= n; i ++ ) { 
		scanf( "%d", &a[i] );
		if( la[ a[i] ] != -1 ) 
			add_edge( la[ a[i] ], i );
		if( la[ a[i] - 1 ] != -1 ) 
			add_edge( i, la[ a[i] - 1 ] );
		la[ a[i] ] = i;
	}

	int cur_id = n;
	std::priority_queue<int> q;
	for( int i = 1; i <= n; i ++ ) {
		if( in[i] == 0 ) {
			q.push(-i);
		}
	}

	while( !q.empty() ) {
		int cur = -q.top(); q.pop();
		b[cur] = cur_id;
		cur_id --;
		for( int i = ehead[cur]; i; i = e[i].next ) {
			int to = e[i].to;
			in[to] --; out[cur] --;
			if( in[to] == 0 ) 
				q.push(-to);
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		p[i] = INF;
		c[ n - i + 1 ] = b[i];
	}

	long long ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		int pos = query( 1, n, c[i] );
		p[ pos + 1 ] = std::min( p[ pos + 1 ], c[i] );
		ans += pos + 1LL;
	}

	printf( "%lld\n", ans );
}
