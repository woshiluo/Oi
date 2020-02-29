#include <cstdio>
#include <cstring>

const int N = 110;
const int INF = 0x3f3f3f3f;

int n;
char s[N];
int f[N][N];
int la[N][N];

void pr( int left, int rig ) {
	if( left > rig ) 
		return ;
	if( la[left][rig] == -1 ) {
		printf( "%c", s[left] );
		pr( left + 1, rig - 1 );
		printf( "%c", s[rig] );
		return ;
	}
	else if( la[left][rig] == 0 ) {
		if( s[left] == '(' || s[left] == ')' )
			printf( "()" );
		else 
			printf( "[]" );
		return ;
	}
	pr( left, la[left][rig] );
	pr( la[left][rig] + 1, rig );
}

int main() {
#ifdef woshiluo
	freopen( "poj.1141.in", "r", stdin );
	freopen( "poj.1141.out", "w", stdout );
#endif
	while( fgets( s + 1, 110, stdin ) ) {
		memset( f, 0, sizeof(f) );
		memset( la, 0, sizeof(la) );
		n = strlen( s + 1 );
		n --;
		if( n == 0 ) {
			printf( "\n" );
			continue;
		}
		for( int i = 1; i <= n; i ++ )
			f[i][i] = 1;
		for( int len = 2; len <= n; len ++ ) {
			for( int left = 1, rig = len; rig <= n; left ++, rig ++ ) {
				f[left][rig] = INF;
				if( ( s[left] == '[' && s[rig] == ']' ) || ( s[left] == '(' && s[rig] == ')' ) ) {
					la[left][rig] = -1;
					f[left][rig] = f[ left + 1 ][ rig - 1 ];
				}
				for( int mid = left; mid < rig; mid ++ ) {
					if( f[left][mid] + f[ mid + 1 ][rig] < f[left][rig] ) {
						la[left][rig] = mid;
						f[left][rig] = f[left][mid] + f[ mid + 1 ][rig]; 
					}
				}
			}
		}
		pr( 1, n );
		printf( "\n" );
	}
}
