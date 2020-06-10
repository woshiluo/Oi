#include <cstdio>
#include <cstring>

#include <algorithm>

const int N = 110;
int n;
int save[N];
char name[N][30];

int main() {
//	freopen( "save.in", "r", stdin );
//	freopen( "save.out", "w", stdout );

	scanf( "%d", &n );
	char str[210];
	int max = 0;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%s", name[i] );
		scanf( "%s", str );
		int len = strlen( str ), cnt = 0;
		for( int i = 1; i < len - 1; i ++ ) {
			if( str[i] == 'o' && str[ i - 1 ] == 's' && str[ i + 1 ] == 's' )
				cnt ++;
		}
		save[i] = cnt;
		if( cnt > max ) 
			max = cnt;
	}
	for( int i = 1; i <= n; i ++ ) {
		if( save[i] == max ) 
			printf( "%s ", name[i] );
	}
	printf( "\n%d", max );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
