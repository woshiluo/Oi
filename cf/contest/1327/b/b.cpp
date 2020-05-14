#include <cstdio>
#include <cstring>

const int N = 1e5 + 1e4;

int t;
int n;
int a[N], b[N];
bool vis[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &t );
	while( t -- ) {
		memset( vis, 0, sizeof(vis) );
		int left = -1;
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			bool flag = false;
			scanf( "%d", &tmp );
			for( int j = 1; j <= tmp; j ++ ) {
				int tmp2;
				scanf( "%d", &tmp2 );
				if( flag == false && vis[ tmp2 ] == false ) {
					vis[ tmp2 ] = true;
					flag = true;
				}
			}
			if( flag == false ) 
				left = i;
		}
		if( left == -1 ) {
			printf( "%s\n", "OPTIMAL" );
		}
		else {
			int rig = left;
			for( int i = 1; i <= n; i ++ ) {
				if( vis[i] == false ) {
					rig = i;
					break;
				}
			}
			printf( "%s\n%d %d\n", "IMPROVE", left, rig );
		}
	}
}
