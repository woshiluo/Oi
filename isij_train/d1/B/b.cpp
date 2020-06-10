#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;

int len1, len2;
char str[110];
int a[110], b[110];
int f[110][11][2];

inline int add( int a, int b ) { return ( a + b ) % mod; }
inline void add_eq( int &a, int b ) { a = ( a + b ) % mod; }


int query( int a[], int len ) {
	memset( f, 0, sizeof(f) );
	for( int i = 0; i < a[0]; i ++)  {
		f[0][i][0] = 1;
	}
	f[0][a[0]][1] = 1;
	for( int i = 1; i < len; i ++ ) {
		int la = i - 1;
		for( int j = 0; j <= 9; j ++ ) {
			for( int k = 0; k <= j; k ++ ) {
				// f[i][j][0] += f[la][k][0];
				add_eq( f[i][j][0], f[la][k][0] );
			}
			if( j < a[i] ) {
				for( int k = 0; k <= j; k ++ ) {
					// f[i][j][0] += f[la][k][1];
					add_eq( f[i][j][0], f[la][k][1] );
				}
			}
			else if( j == a[i] ) {
				for( int k = 0; k <= j; k ++ ) {
					// f[i][j][1] += f[la][k][1];
					add_eq( f[i][j][1], f[la][k][1] );

				}
			}
		}
	}
	int res = 0;
	for( int i = 0; i <= 9; i ++ ) {
//		res += f[ len - 1 ][i][0] + f[ len - 1 ][i][1];
		add_eq( res, add( f[ len - 1 ][i][0], f[ len - 1 ][i][1] ) );
	}
	return res;
}

bool chk( int a[], int len ) {
	for( int i = 1; i < len; i ++ ){
		if( a[ i - 1 ] > a[i] ) 
			return false;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%s", str );
	len1 = strlen(str);
	for( int i = 0; i < len1; i ++ ) {
		a[i] = str[i] - '0';
	}
	scanf( "%s", str );
	len2 = strlen(str);
	for( int i = 0; i < len2; i ++ ) {
		b[i] = str[i] - '0';
	}

	printf( "%d\n", ( ( add( query( b, len2 ), - query( a, len1 ) ) + mod ) % mod ) + chk( a, len1 ) );
}
