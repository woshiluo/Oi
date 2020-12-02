// Woshiluo<woshiluo@woshiluo.site>
// 2020/11/17 23:33:21 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 1e3 + 1e2;

struct node { int x1, y1, x2, y2, x3, y3; };

int main() {
#ifdef woshiluo
	freopen( "c2.in", "r", stdin );
	freopen( "c2.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n, m;
		bool mp[N][N];
		std::vector<node> ans;
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				int tmp;
				scanf( "%1d", &tmp );
				mp[i][j] = ( tmp == 1 );
			}
		}

		for( int i = 1; i <= n - 2; i ++ ) {
			for( int j = 1; j < m; j ++ ) {
				if( mp[i][j] ) {
					ans.push_back( (node) { i, j, i + 1, j, i + 1, j + 1 } );
					mp[i][j] ^= 1;
					mp[ i + 1 ][j] ^= 1;
					mp[ i + 1 ][ j + 1 ] ^= 1;
				}
			}
			if( mp[i][m] ) {
				ans.push_back( (node) { i, m, i + 1, m, i + 1, m - 1 } );
				mp[i][m] ^= 1;
				mp[ i + 1 ][m] ^= 1;
				mp[ i + 1 ][ m - 1 ] ^= 1;
			}
		}

		for( int j = 1; j <= m - 2; j ++ ) {
			if( mp[ n - 1 ][j] && mp[n][j] ) {
				ans.push_back( (node) { n - 1, j, n, j, n, j + 1 } );
				mp[ n - 1 ][j] ^= 1; mp[n][j] ^= 1; mp[n][ j + 1 ] ^= 1;
			}
			else if( mp[ n - 1 ][j] ) {
				ans.push_back( (node) { n - 1, j, n - 1, j + 1, n, j + 1 } );
				mp[ n - 1 ][j] ^= 1; mp[ n - 1 ][ j + 1 ] ^= 1; mp[n][ j + 1 ] ^= 1;
			}
			else if( mp[n][j] ) {
				ans.push_back( (node) { n, j, n - 1, j + 1, n, j + 1 } );
				mp[n][j] ^= 1; mp[ n - 1 ][ j + 1 ] ^= 1; mp[n][ j + 1 ] ^= 1;
			}
		}

		int base_x = n - 1, base_y = m - 1;
#define node1 base_x, base_y
#define node2 base_x, base_y + 1
#define node3 base_x + 1, base_y
#define node4 base_x + 1, base_y + 1
		// Okay, let us do sth funny.
		bool p1 = mp[base_x][base_y];
		bool p2 = mp[base_x][base_y + 1];
		bool p3 = mp[base_x + 1][base_y];
		bool p4 = mp[base_x + 1][base_y + 1];
		// 1 2 3 4
		if( p1 && p2 && p3 && p4 ) {
			ans.push_back( (node) { node1, node2, node3 } );
			ans.push_back( (node) { node4, node1, node2 } );
			ans.push_back( (node) { node4, node3, node2 } );
			ans.push_back( (node) { node4, node3, node1 } );
		}
		// 1 2 3
		if( p1 && p2 && p3 && !p4 ) {
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 1 2 4
		if( p1 && p2 && !p3 && p4 ) {
			ans.push_back( (node) { node1, node2, node4 } );
		}
		// 1 2
		if( p1 && p2 && !p3 && !p4 ) {
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node2, node3, node4 } );
		}
		// 1 3 4
		if( p1 && !p2 && p3 && p4 ) {
			ans.push_back( (node) { node1, node3, node4 } );
		}
		// 1 4
		if( p1 && !p2 && !p3 && p4 ) {
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node2, node3, node4 } );
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 1 3
		if( p1 && !p2 && p3 && !p4 ) {
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node3, node2, node4 } );
		}
		// 1 
		if( p1 && !p2 && !p3 && !p4 ) {
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 2 3 4
		if( !p1 && p2 && p3 && p4 ) {
			ans.push_back( (node) { node2, node3, node4 } );
		}
		// 2 3 
		if( !p1 && p2 && p3 && !p4 ) {
			ans.push_back( (node) { node1, node2, node3 } );
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 2 4
		if( !p1 && p2 && !p3 && p4 ) {
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 2
		if( !p1 && p2 && !p3 && !p4 ) {
			ans.push_back( (node) { node1, node3, node2 } );
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node3, node2, node4 } );
		}
		// 3 4
		if( !p1 && !p2 && p3 && p4 ) {
			ans.push_back( (node) { node2, node3, node4 } );
			ans.push_back( (node) { node1, node3, node2 } );
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node3, node2, node4 } );
		}
		// 3
		if( !p1 && !p2 && p3 && !p4 ) {
			ans.push_back( (node) { node2, node3, node4 } );
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node3 } );
		}
		// 4
		if( !p1 && !p2 && !p3 && p4 ) {
			ans.push_back( (node) { node1, node3, node4 } );
			ans.push_back( (node) { node1, node2, node4 } );
			ans.push_back( (node) { node3, node2, node4 } );
		}
		printf( "%d\n", ans.size() );
		for( auto x: ans ) {
			printf( "%d %d %d %d %d %d\n", x.x1, x.y1, x.x2, x.y2, x.x3, x.y3 );
		}
	}
}
