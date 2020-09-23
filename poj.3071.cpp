#include <cstdio>

const int N = 1100;

int n;
double p[N][N];
double f[N];

void dfs( int left, int rig ) {
	if( left == rig ) {
		f[left] = 1;
		return ;
	}
	int mid = ( left + rig ) >> 1;
	dfs( left, mid );
	dfs( mid + 1, rig );

	double la[N];
	for( int i = left; i <= rig; i ++  )
		la[i] = f[i];

	for( int i = left; i <= mid; i ++ ) {
		double cur = f[i];
		f[i] = 0;
		for( int j = mid + 1; j <= rig; j ++ ) {
			f[i] += ( cur * la[j] * p[i][j] );
		}
	}
	for( int i = mid + 1; i <= rig; i ++ ) {
		double cur = f[i];
		f[i] = 0;
		for( int j = left; j <= mid; j ++ ) {
			f[i] += ( cur * la[j] * p[i][j] );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "poj.3071.in", "r", stdin );
	freopen( "poj.3071.out", "w", stdout );
#endif
	while(1) {
		scanf( "%d", &n );
		if( n == -1 ) 
			break;
		n = ( 1 << n );
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= n; j ++  ){
				scanf( "%lf" ,&p[i][j] );
			}
		}

		dfs( 1, n );

		int max_id = 0;
		for( int i = 1; i <= n; i ++ ) {
			if( f[i] > f[ max_id ] )
				max_id = i;
		}

		printf( "%d\n", max_id );
	}
}
