#include <cstdio>

#include <queue>
#include <vector>
#include <algorithm>

inline int aabs( int a ) { return a < 0? -a: a; }

const int N = 110000;

int b, n, d, m;

namespace board1 {/*{{{*/
	struct node {
		int x;
	} ani[N];
	inline int dis( int x, int y ) {
		return aabs( ani[x].x - ani[y].x );
	}
	bool cmp( node a, node b ) {
		return a.x < b.x;
	}
	void calc() {
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &ani[i].x );
		}
		long long ans = 0;
		int p1 = 1, p2 = 1;
		std::sort( ani + 1, ani + n + 1, cmp );
		for( int i = 1; i <= n; i ++ ) {
			if( p2 < i )
				p2 = i;
			while( dis( p1, i ) > d && p1 < i )
				p1 ++;
			while( dis( p2, i ) < d && p2 > i ) 
				p2 ++;
			if( dis( p2, i ) > d )
				p2 --;
			ans += 1LL * ( p2 - p1 );
		}
		printf( "%lld\n", ans );
	}
}/*}}}*/

namespace board2 {/*{{{*/
	struct node {/*{{{*/
		int x, y;
	} ani[N];

	bool cmp( node a, node b ) {
		if( a.x == b.x ) 
			return a.y < b.y;
		return a.x < b.x;
	}/*}}}*/

	int BIT[80000 * 3];/*{{{*/
	const int MAX_M = 75000 * 3 + 100;
	inline int lowbit( int cur ) { return cur & ( - cur ); }
	void add( int cur, int val ) {
		if( cur == 0 ) 
			return ;
		for( ; cur <= MAX_M; cur += lowbit(cur) )
			BIT[cur] += val;
	}
	int query( int cur ) {
		int val = 0;
		for( ; cur; cur -= lowbit(cur) ) {
			val += BIT[cur];
		}
		return val;
	}
	inline int ask( int from, int to ) {
		if( from <= 0 ) 
			from = 1;
		if( to > MAX_M ) 
			to = MAX_M;
		return query(to) - query(from - 1);
	}/*}}}*/

	void calc() {
		std::vector<int> num;
		for( int i = 1; i <= n; i ++ ) {
			int tmp_x, tmp_y;
			scanf( "%d%d", &tmp_x, &tmp_y );
			ani[i].x = tmp_x + tmp_y;
			ani[i].y = tmp_x - tmp_y + 75005;
			num.push_back( ani[i].x );
			num.push_back( ani[i].x + d );
		}
		std::sort( num.begin(), num.end() );
		int cnt = std::unique( num.begin(), num.end() ) - num.begin();
		long long ans = 0;
		std::sort( ani + 1, ani + n + 1, cmp );
		std::queue<node> q;
		int p1 = 1;
		for( int i = 0; i < cnt; i ++ ) {
			while( p1 <= n && ani[p1].x == num[i] ) {
				add( ani[p1].y, 1 );
				q.push( (node){ ani[p1].x + d, ani[p1].y} );
				p1 ++;
			}
			while( !q.empty() ) {
				node cur = q.front();
				if( cur.x != num[i] )
					break;
				add( cur.y, -1 );
				ans += 1LL * ask( cur.y - d, cur.y + d );
				q.pop();
			}
		}
		printf( "%lld\n", ans );
	}
}/*}}}*/

namespace board3 {/*{{{*/
	struct node {
		int x, y, z;
	} ani[N];
	inline int dis( int x, int y ) {
		return aabs( ani[x].x - ani[y].x )
			+ aabs( ani[x].y - ani[y].y )
			+ aabs( ani[x].z - ani[y].z );
	}
	int mp[300][300][300];
	int sum[300][300][300];
	inline int s( int z, int i, int j, int x, int y ) {
		if( i < 0 ) 
			i = 1;
		if( j < 0 ) 
			j = 1;
		if( x > 226 )
			x = 226;
		if( y > 226 ) 
			y = 226;
		if( i == 0 || j == 0 ) {
			int res = sum[z][x][y];
			if( i != 0 ) 
				res -= sum[z][ i - 1 ][y];
			if( j != 0 )
				res -= sum[z][x][ j - 1 ];
			return res;
		}
		return sum[z][x][y] + sum[z][ i - 1 ][ j - 1 ] - sum[z][ i - 1 ][y] - sum[z][x][ j - 1 ];
	}
	void calc() {
		for( int i = 1; i <= n; i ++ ) {
			int tmp_x, tmp_y;
			scanf( "%d%d%d", &tmp_x, &tmp_y, &ani[i].z );
			ani[i].x = tmp_x + tmp_y + 76;
			ani[i].y = tmp_x - tmp_y + 76;
			mp[ ani[i].z ][ ani[i].x ][ ani[i].y ] ++;
		}
		long long ans = 0;
		for( int z = 1; z <= 75; z ++ ) {
			for( int x = 1; x <= 226; x ++ ) {
				for( int y = 1; y <= 226; y ++ ) {
					sum[z][x][y] = sum[z][x][ y - 1 ] + sum[z][ x - 1 ][y] - sum[z][ x - 1 ][ y - 1 ]
						+ mp[z][x][y];
				}
			}
		}
		for( int i = 1; i <= n; i ++ ) {
			for( int z = 0; z <= 75; z ++ ) {
				int tmp = d - aabs( ani[i].z - z );
				if( tmp < 0 ) 
					continue;
				int x = ani[i].x, y = ani[i].y;
				int _i = x - tmp, _j = y - tmp;
				x = x + tmp, y = y + tmp;
				ans += 1LL * s( z, _i, _j, x, y );
			}
			ans --;
		}
		printf( "%lld\n", ans >> 1 );
	}
}/*}}}*/

int main() {
#ifdef woshiluo
	freopen( "board.in", "r", stdin );
	freopen( "board.out", "w", stdout );
#endif
	scanf( "%d%d%d%d", &b, &n, &d, &m );
	if( b == 1 ) 
		board1::calc();
	if( b == 2 ) 
		board2::calc();
	if( b == 3 ) 
		board3::calc();
}
