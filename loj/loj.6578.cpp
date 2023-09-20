#include <cstdio>

const int N = 1e4 + 1e3;

int n, a, b, h;
int f[N];

int main() {
	scanf( "%d%d%d%d", &n, &a, &b, &h );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = i + 1; j <= n; j ++ ) {
			if( check( i, j ) == false ) {
				rig[i] = j - 1;
				break;
			}
		}
		if( check( i, n ) ) 
			rig[i] = n;
	}
}
