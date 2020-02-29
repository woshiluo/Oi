#include <cstdio>
#include <cstring>

inline int Min( int _a, int _b ) { return _a < _b ? _a: _b; }

const int N = 110;

int n;
int f[N][N], numlen[N];
char s[N];

bool check( int l1, int r1, int l2, int r2, int len1, int len2 ) {
	if( len2 % len1 != 0 )
		return false;
	int p1 = l1, p2 = l2;
	while( p2 <= r2 ) {
		if( s[p1] != s[p2] ) 
			return false;
		p1 ++, p2 ++;
		if( p1 > r1 )
			p1 = l1;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4302.in", "r", stdin );
	freopen( "luogu.4302.out", "w", stdout );
#endif
	scanf( "%s", s + 1 );
	n = strlen( s + 1 );

	for( int i = 1; i <= n; i ++ ) {
		numlen[i] = numlen[ i / 10 ] + 1;
		f[i][i] = 1;
	}

	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			f[left][rig] = len;
			for( int mid = left; mid < rig; mid ++ ) {
				int len1 = mid - left + 1, len2 = len;
				if( check( left, mid, left, rig, len1, len2 ) ) 
					f[left][rig] = Min( f[left][rig], f[left][mid] + numlen[ len2 / len1 ] + 2 );
				f[left][rig] = Min( f[left][rig], f[left][mid] + f[ mid + 1 ][rig] ) ;
			}
		}
	}

	printf( "%d\n", f[1][n] );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
