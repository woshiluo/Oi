#include <cmath>
#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

const int N = 2100;
const double eps = 1e-7;

int n, m;
char T[N];

int node_cnt = 1;
struct ac_node {
	int nxt[20], fail;
	double val, cnt;
	ac_node() {
		memset( nxt, 0, sizeof(nxt) );
		fail = 1;
		val = cnt = 0;
	}
} tree[ N * 10 ];

void insert( char *s, double val ) {
	int cur = 1;
	for( ; *s; s ++ ) {
		int cur_char = *s - '0';
		int &nxt = tree[cur].nxt[cur_char];
		if( nxt == 0 ) {
			node_cnt ++;
			nxt = node_cnt;
		}
		cur = nxt;
	}
	tree[cur].cnt ++;
	tree[cur].val += val;
}

void build() {
	std::queue<int> q;
	for( int i = 0; i < 20; i ++ ) {
		if( tree[1].nxt[i] == 0 ) 
			tree[1].nxt[i] = 1;
		else 
			q.push( tree[1].nxt[i] );
	}
	while( !q.empty() ) {
		int cur = q.front(); q.pop();
		int fail = tree[cur].fail;
		tree[cur].cnt += tree[fail].cnt;
		tree[cur].val += tree[fail].val;
		for( int i = 0; i < 10; i ++ ) {
			if( tree[cur].nxt[i] ) {
				tree[ tree[cur].nxt[i] ].fail = tree[fail].nxt[i];
				q.push( tree[cur].nxt[i] );
			}
			else 
				tree[cur].nxt[i] = tree[fail].nxt[i];
		}
	}
}

double f[N][N];
struct last { int la, cur_char; } la[N][N];

char ans[N];
void update_ans( int id, int pos ) {
	if( id != 1 ) 
		update_ans( id - 1, la[id][pos].la );
	ans[id] = la[id][pos].cur_char + '0';
}

inline void update( double &cur, double nxt, last &la, last upd ) {
	if( nxt > cur ) {
		cur = nxt;
		la = upd;
	}
}

bool check( double mid ) {
	double INF = 1e16;
	for( int i = 0; i <= n; i ++ ) {
		for( int j = 0; j <= node_cnt; j ++ ) {
			f[i][j] = -INF;
		}
	}
	f[0][1] = 0;
	
	for( int i = 1; i <= n; i ++ ) {
		if( T[i] == '.' ) {
			for( int j = 1; j <= node_cnt; j ++ ) {
				for( int k = 0; k < 10; k ++ ) {
					if( f[ i - 1 ][j] == -INF )
						continue;
					int nxt = tree[j].nxt[k];
					update( f[i][nxt], f[ i - 1 ][j] + tree[nxt].val - tree[nxt].cnt * mid, 
							la[i][nxt], (last){ j, k } );
				}
			}
		}
		else {
			int k = T[i] - '0';
			for( int j = 1; j <= node_cnt; j ++ ) {
				if( f[ i - 1 ][j] == -INF )
					continue;
				int nxt = tree[j].nxt[k];
				update( f[i][nxt], f[ i - 1 ][j] + tree[nxt].val - tree[nxt].cnt * mid,
						la[i][nxt], (last){ j, k } );
			}
		}
	}

	int pos = 0;
	for( int i = 1; i <= node_cnt; i ++ ) {
		if( f[n][i] > f[n][pos] ) 
			pos = i;
	}
	if( f[n][pos] > 0 ) {
		update_ans( n, pos );
		return 1;
	}
	return 0;
}

void write( int x, int pos ) {
	if( x != 1 ) 
		write( x - 1, la[x][pos].la );
	printf( "%d", la[x][pos].cur_char );
}

int main() {
#ifdef woshiluo
	freopen( "loj.3089.in", "r", stdin );
	freopen( "loj.3089.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	scanf( "%s", T + 1 );
	double left = 0, rig = 0;
	for( int i = 1; i <= m; i ++ ) {
		double val;
		char str[N];
		scanf( "%s%lf", str + 1, &val );
		val = std::log( val );
		rig = std::max( rig, val );
		insert( str + 1, val );
	}

	build();

	while( left + eps <= rig ) {
		double mid = ( left + rig ) / 2;
		if( check(mid) ) {
			left = mid + eps;
		}
		else 
			rig = mid - eps;
	}

	printf( "%s\n", ans + 1 );
}
