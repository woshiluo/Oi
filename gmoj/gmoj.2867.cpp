#include <cstdio>
#include <cstring>

inline double abs( double a ) { return a < 0? ( 0.0 - a ): a; }
inline int Min( int a, int b ) { return a < b? a: b; }
inline int Max( int a, int b ) { return a > b? a: b; }

const double eqs = 0.000000001;

int n, r, q, s, cnt;
int pos[110][110];

// double dfs( int now, int combo, int life, double p ) {
// 	if( life == 0 || now == n ) 
// 		return 0.0;
// 	
// 	return p * ( dfs( now + 1, combo + 1, Min( life + 1, q ), p ) + Min( combo + 1, r ) ) + ( 1.0 - p ) * dfs( now + 1, 0, life - 1, p );
// }

struct matrix {
	double mat[110][110];
	matrix( double now = 0.0 ) {
		memset( mat, 0, sizeof(mat) );
		if( now != 0.0 ) {
			for( int i = 0; i < 100; i++ )
				mat[i][i] = now;
		}
	}
	matrix operator* ( matrix b ) {
		matrix res;
		for( int i = 1; i <= cnt; i++ ) {
			for( int j = 1; j <= cnt; j++ ) {
				for( int k = 1; k <= cnt; k++ ) {
					res[i][j] += mat[i][k] * b[k][j];
				}
			}
		}
		return res;
	}
	double* operator[] ( int now ) { return mat[now]; }
};

matrix ksm( matrix a, int p ) {
	matrix res(1);
	while(p) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}

bool check( double p ) {
	matrix a;

	a[1][1] = 1; 
	for( int i = 1; i <= q; i++ ) {
		int tmp = ( i == q )? r: Min( i - 1, r );
		for( int j = 0; j <= Max( 0, tmp ); j++ ) {
			int x = pos[i][j], y = pos[ i - 1 ][0], z = pos[ Min( i + 1, q ) ][ Min( j + 1, r ) ];
			if( i > 1 ) 
				a[x][y] = ( 1.0 - p );
			a[x][z] = p;
			a[x][1] = p * (double)Min( j + 1, r );
		}
	}

//	printf("%lf\n", ksm( a, n )[ pos[q][0] ][1]);
	return ( ksm( a, n )[ pos[q][0] ][1] ) > s;
}

int main() {
#ifdef woshiluo
	freopen( "gmoj.2867.in", "r", stdin );
	freopen( "gmoj.2867.out", "w", stdout );
#endif 
	scanf( "%d%d%d%d", &n, &r, &q, &s );

	for( int i = 0; i <= q; i++ ) {
		int tmp = ( i == q )? r: Min( i - 1, r );
		for( int j = 0; j <= Max(0, tmp); j++ ) {
			pos[i][j] = ++ cnt;
		}
	}

	if ( !check(1) ) {
		printf("Impossible.");
		return 0;
	}
	double left = 0, rig = 1, res = 10;
	while( abs( rig - left ) >= eqs ) {
		double mid = ( left + rig ) / 2;
		if( check(mid) ) 
			res = res < mid? res: mid, rig = mid;
		else
			left = mid;
	}

	printf( "%.6lf", res );
}
