#include <cstdio>

char a[10], b[10] = "abcd";
int n , k, ans = 0;

void chk() {
	int cnt = 0;
	for( int i = 0; i < n; i ++ ) {
		for( int j = i; j < n; j ++ ) {
			for( int k = i; k <= j; k ++ ) {
				if( a[k] > b[k] ) {
					cnt ++;
					break;
				}
				if( a[k] < b[k] ) 
					break;
			}
		}
	}
	if( cnt == k ) {
		ans ++;
		printf( "%s\n", a );
	}
}

void dfs( int dep ) {
	if( dep == n ) {
		chk();
		return ;
	}
	for( int i = 0; i < 26; i ++ ) {
		a[dep] = 'a' + i;
		dfs( dep + 1 );
	}
}

int main() {
	freopen( "temp.in", "r", stdin );
	freopen( "temp.out", "w", stdout );
	scanf( "%d%d", &n, &k );
	scanf( "%s", b );
	dfs( 0 );
	printf( "%d\n", ans );
}
