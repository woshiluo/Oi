#include <cstdio>

inline int Min( int a, int b ) { return a < b? a: b; }

const int N = 1100;
const int INF = 0x3f3f3f3f;

int n, m, a, b, c, d;
int mp[N][N], sum[N][N], room[N][N], min[N][N];

inline int s( int i, int j, int x, int y ) {
	return sum[x][y] + sum[ i - 1 ][ j - 1 ] - sum[ i - 1 ][y] - sum[x][ j - 1 ];
}

class SegmentTree {
	public:
	inline int ask( int from, int to ) {
		if( to > n ) to = n;
		if( to < from ) 
			return 0;
		return query( 1, 1, n, from, to );
	}
	inline void init( int size, int a[] ) {
		n = size + 10;
		build( 1, 1, n, a );
	}
	private:
	int tree[ N << 3 ], n;
	inline void push_up( int cur ) { tree[cur] = Min( tree[ cur << 1 ], tree[ cur << 1 | 1 ] ); }
	int query( int cur, int left, int rig, int from, int to ) {
		if( from <= left && rig <= to ) 
			return tree[cur];

		int mid = ( left + rig ) >> 1, res = INF;
		if( from <= mid )
			res = Min( res, query( cur << 1, left, mid, from, to ) );
		if( to > mid ) 
			res = Min( res, query( cur << 1 | 1, mid + 1, rig, from, to ) );
		
		return res;
	}
	void build( int cur, int left, int rig, int a[] ) {
		tree[cur] = INF;
		if( left == rig ) {
			tree[cur] = a[left];
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid, a );
		build( cur << 1 | 1, mid + 1, rig, a );
		push_up( cur );
	}
};

int main() {
#ifdef woshiluo 
	freopen( "pyramid.in", "r", stdin );
	freopen( "pyramid.out", "w", stdout );
#endif

	scanf( "%d%d%d%d%d%d", &m, &n, &a, &b, &c, &d );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%d", &mp[i][j] );
			sum[i][j] = sum[ i - 1 ][j] + sum[i][ j - 1 ] + mp[i][j] - sum[ i - 1 ][ j - 1 ];
		}
	}
	for( int i = 1; i <= n; i ++ ) {
		if( i + d - 1 > n ) 
			break;
		for( int j = 1; j <= m; j ++ ) {
			if( j + c - 1 > m )
				break;
			int x = i + d - 1, y = j + c - 1;
			room[i][j] = s( i, j, x, y );
#ifdef woshiluo
			printf( "%3d ", room[i][j] );
#endif
		}
#ifdef woshiluo
		printf( "\n" );
#endif
	}
#ifdef woshiluo
		printf( "\n" );
#endif

	SegmentTree rm;
	for( int i = 1; i <= n; i ++ ) {
		if( i + d - 1 > n ) 
			break;
		rm.init( m, room[i] );
		for( int j = 1; j <= m; j ++ ) {
			if( j + c - 1 > m )
				break;
			min[j][i] = rm.ask( j, j + ( a - 2 - c + 1 ) - 1 );
#ifdef woshiluo
			printf( "%3d ", min[j][i] );
#endif
		}
#ifdef woshiluo
		printf( "\n" );
#endif
	}

	int ans = 0, ans_x = 0, ans_y = 0;
	for( int j = 1; j <= m; j ++ ) {
		if( j + a - 1 > m )
			break;
		rm.init( n, min[ j + 1 ] );
		for( int i = 1; i <= n; i ++ ) {
			if( i + b - 1 > n ) 
				break;
			int x = i + b - 1, y = j + a - 1;
			int cur_s = s( i, j, x, y );
			int res = cur_s - rm.ask( i + 1, x - 1 - d + 1 );
			if( res > ans ) {
#ifdef woshiluo
				printf( "( %d, %d ): %d\n min: %d \n", i, j, res, rm.ask( i + 1, x - 1 ) );
#endif
				ans_x = i, ans_y = j;
				ans = res;
			}
		}
	}
	
	printf( "%d %d\n", ans_y, ans_x );

	ans = INF;
	int _ans_x = 0, _ans_y = 0;
	for( int i = ans_x + 1; i <= ans_x + b - 2; i ++ ) {
		if( i + d - 1 > ans_x + b - 2 ) 
			break;
		for( int j = ans_y + 1; j <= ans_y + a - 2; j ++ ) {
			if( j + c - 1 > ans_y + a - 2 )
				break;
#ifdef woshiluo
			printf( "( %d, %d ): %d \n", i, j, room[i][j] );
#endif
			if( room[i][j] < ans ) {
				ans = room[i][j];
				_ans_x = i, _ans_y = j;
			}
		}
	}
	printf( "%d %d\n", _ans_y, _ans_x );

	return 0;
}
