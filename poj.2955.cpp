#include <cstdio>
#include <cstring>

inline int Max( int a, int b ) { return a > b? a: b; }

const int N = 210;
const int INF = 0x3f3f3f3f;

int n;
char s[N];
int f[N][N];

void init() {
	memset( f, 0, sizeof(f) );
}

void dp() {
	for( int len = 2; len <= n; len ++ ) {
		for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
			if( ( s[left] == '(' && s[rig] == ')' ) || ( s[left] == '[' && s[rig] == ']' )) 
				f[left][rig] = f[ left + 1 ][ rig - 1 ] + 2;
			for( int mid = left; mid < rig; mid ++ ) {
				f[left][rig] = Max( f[left][rig], f[left][mid] + f[ mid + 1 ][rig] );
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "poj.2955.in", "r", stdin );
	freopen( "poj.2955.out", "w", stdout );
#endif
	while( scanf( "%s", s + 1 ) != EOF ) {
		if( s[1] == 'e' ) 
			break;
		n = strlen( s + 1 );
		init(), dp();
		printf( "%d\n", f[1][n] );
	}
}
