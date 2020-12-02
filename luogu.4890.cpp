#include <cstdio>

const int N = 2100;

int n, k;
int f[N][N][2];

int main() {
	scanf( "%d%d", &n, &k );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].left, &a[i].rig );
		out[ a[i].left ] = i; in[ a[i].rig ] = i;
	}

	for( int i = 1; i <= n; i ++ ) {
		if( in[i] ) {
		}
		else if( out[i] ) {
			for( int j = 1; j < i; j ++ ) {
				chk_Min( f[i][0], f[j][0] );
				chk_Min( f[i][1], f[j][0] );
			}
		}
	}
}
