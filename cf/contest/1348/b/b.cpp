// Woshiluo<woshiluo@woshiluo.site>
// 2020/05/01 22:48:24 
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

int T;
int n, k, cnt;
int a[N], ans[N * N];
bool vis[N];


int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );

	while( T -- ) {
		scanf( "%d%d", &n, &k );
		cnt = 0;
		memset( vis, 0, sizeof( vis ) );
		std::vector<int> dis;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( !vis[ a[i] ] ) {
				cnt ++;
				dis.push_back( a[i] );
				vis[ a[i] ] = true;
			}
		}
		std::sort( dis.begin(), dis.end() );
		int p1 = 0, len = 0;
		if( cnt > k ) {
			printf( "-1\n" );
			continue;
		}
		while( cnt < k ) {
			dis.push_back( dis[ dis.size() - 1 ] );
			cnt ++;
		}
		for( int i = 1; i <= n; i ++ ) {
			while( a[i] != dis[p1] ) {
				len ++;
				ans[len] = dis[p1];
				p1 ++;
				if( p1 == cnt )
					p1 = 0;
			}
			len ++;
			ans[len] = a[i];
			p1 ++;
			if( p1 == cnt )
				p1 = 0;
		}
		printf( "%d\n", len  );
		for( int i = 1; i <= len; i ++  ) {
			printf( "%d ", ans[i] );
		}
		printf( "\n" );
	}
}
