#include <cstdio>

const int N = 12;
const int N_2 = 1 << 13;

int n, m;
bool fig[N];
int f[ N_2 ][ N_2 ];

void dfs( int now, int dep ) {
	for( int i = 0; i <= bit[ dep - 1 ]; i ++ ) {
	}
	fig[now] = true;

}

int main() {
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= bit[ n - 1 ]; i ++ ) {
		for( int j = 1; j < n; j ++ ){
			scanf( "%d", &fig[ bit[ n - 1 ] - 1 + i ][j] );
		}
	}
	for( int i = 1; i <= bit[ n - 1 ]; i ++ ) {
		for( int j = 1; j < n; j ++ ){
			scanf( "%d", &far[ bit[ n - 1 ] - 1 + i ][j] );
		}
	}

	dfs( 1, n );
}
