#include <cstdio>

inline int Min( int a, int b ) { return a < b? a: b; }
inline int aabs( int a ) { return a < 0? -a: a; }

const int N = 510;
const int INF = 0x3f3f3f3f;

int n, m, k, out_len;
bool vis[N][N];
char out[ N * N ];
struct node{ int x, y; };

node a[N], b[N], c[N];

int calc_dis( node from, node to ) { return aabs( to.x - from.x ) + aabs( to.y - from.y ); }

void output( node from, node to ) {
	for( int i = from.x; i < to.x; i ++ ) {
		out[ ++ out_len ] = 'U';
	}
	for( int i = to.x; i < from.x; i ++ ) {
		out[ ++ out_len ] = 'D';
	}

	for( int i = from.y; i < to.y; i ++ ) {
		out[ ++ out_len ] = 'L';
	}
	for( int i = to.y; i < from.y; i ++ ) {
		out[ ++ out_len ] = 'R';
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &k );
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d%d", &a[i].x, &a[i].y );
	}
	for( int i = 1; i <= k; i ++ ) {
		scanf( "%d%d", &b[i].x, &b[i].y );
		c[i].x = a[i].x - b[i].x;
		c[i].y = a[i].y - b[i].y;
	}
	
	node cur = (node){ 0, 0 };
	int base = 210;
	vis[base][base] = true;
	int res = 0;
	while(1) {
		int min_dis = INF, min_id = 0;
		for( int i = 1; i <= k; i ++ ) {
			if( vis[ base + c[i].x ][ base + c[i].y ] )
				continue;
			int tmp_dis = calc_dis( cur, c[i] );
			if( tmp_dis < min_dis ) {
				min_dis = tmp_dis;
				min_id = i;
			}
		}
		if( min_id == 0 ) 
			break;
		vis[ base + c[min_id].x ][ base + c[min_id].y ] = true;
		res += min_dis;
		output( cur, c[min_id] );
		cur = c[min_id];
	}

	if( res > 2 * n * m ) 
		printf( "-1\n" );
	else 
		printf( "%d\n%s", res, out + 1 );
}
