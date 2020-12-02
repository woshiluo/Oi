#include <cstdio>

#include <queue>
#include <algorithm>

const int N = 1e5 + 1e4;

// Edge Start
struct edge { int to, next; };
edge e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

struct node { int d, c, id; };

int n, q;
int nxt[N], col[N], cnt[N];
int fa[N][30], sum[N][30];
node a[N];
// bool vis[N];

//std::vector<int> sum[N], p[N];

// inline int get_ans( int pos, int v ) {
// 	int st = cnt[pos] - 1, res = 0, id = col[pos];
// 	int left = cnt[pos], rig = sum[id].size() - 1;
// 	while( left <= rig ) {
// 		int mid = ( left + rig ) >> 1;
// 		if( sum[id][mid] - sum[id][st] < v ) {
// 			res = mid;
// 			left = mid + 1;
// 		}
// 		else {
// 			rig = mid - 1;
// 		}
// 	}
// 	if( res == 0 ) 
// 		res = st;
// 	res ++;
// 	if( res > sum[id].size() - 1 ) 
// 		return 0;
// 	return p[id][res];
// }

void dfs( int cur, int la ) {
	fa[cur][0] = la; sum[cur][0] = a[cur].c;
	for( int k = 1; k < 25; k ++ ) {
		if( fa[ fa[cur][ k - 1 ] ][ k - 1 ] == 0 )
			continue;
		fa[cur][k] = fa[ fa[cur][ k - 1 ] ][ k - 1 ];
		sum[cur][k] = sum[ fa[cur][ k - 1 ] ][ k - 1 ] + 
			sum[cur][ k - 1 ];
	}
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		dfs( e[i].to, cur );
	}
}

int get_ans( int cur, int val ) {
	for( int k = 24; k >= 0; k -- ) {
		if( fa[cur][k] != 0 && sum[cur][k] < val ) {
			val -= sum[cur][k];
			cur = fa[cur][k];
		}
	}
	if( cur == n + 1 ) 
		return 0;
	return cur;
}

int main() {
	freopen( "fountain.in", "r", stdin );
	freopen( "fountain.out", "w", stdout );

	scanf( "%d%d", &n, &q );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].d, &a[i].c );
		a[i].id = i;
	}
	{
		std::deque<int> q;
		for( int i = n; i >= 1; i --  ) {
			while( !q.empty() && a[i].d >= a[ q.front() ].d ) 
				q.pop_front();
			if( !q.empty() ) {
				nxt[i] = q.front();
				add_edge( i, q.front() );
				add_edge( q.front(), i );
			}
			else {
				add_edge( i, n + 1 );
				add_edge( n + 1, i );
			}
			q.push_front(i);
		}
	}


	dfs( n + 1, 0 );

	while( q -- ) {
		int r, v;
		scanf( "%d%d", &r, &v );
		printf( "%d\n", get_ans( r, v ) );
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
