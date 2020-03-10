#include <cstdio>

#include <queue>
 
inline int Max( int a, int b ) { return a > b? a: b; }

int ans = 0;
int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
bool vis[10];
std::queue<int> q;

void dfs( int now, int dep, int res ) {
	if( dep == 8 ) {
		ans = Max( ans, res + a[now] * a[1] );
		return ;
	}
	for( int i = 1; i <= 8; i ++) {
		if( vis[i] == false ) {
			vis[i] = true;
			dfs( i, dep + 1, res + ( a[now] * a[i] ) );
			vis[i] = false;
		}
	}
}

int main() {
	vis[1] = true;
	dfs( 1, 1, 0 );
	printf( "%d\n", ans );
	
}
