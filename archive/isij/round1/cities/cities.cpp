#include <cstdio>

const int N = 60;

int n;
bool cities[N][N];

void write_ans( int x, int y ) {
	for( int i = 1; i < x; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			printf( "1" );
		}
		printf( "\n" );
	}
	for( int j = 1; j <= y; j ++ ) 
		printf( "1" );
	for( int j = y + 1; j <= n; j ++ ) 
		printf( "2" );
	printf( "\n" );
	for( int i = x + 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			printf( "2" );
		}
		printf( "\n" );
	}
}

int main() {
	freopen( "cities.in", "r", stdin );
	freopen( "cities.out", "w", stdout );

	scanf( "%d", &n );
	int cit_cnt = 0;
	for( int i = 1; i <= n; i ++ ) {
		char s[N];
		scanf( "%s", s + 1 );
		for( int j = 1; j <= n; j ++ ) {
			if( s[j] == 'C' ){
				cities[i][j] = true;
				cit_cnt ++;
			}
		}
	}
	int cur_a = 0, gol = cit_cnt / 2;
	for( int i = 1; i <= n; i ++ ) {
		int tmp_cnt = 0;
		for( int j = 1; j <= n; j ++ ) {
			if( cities[i][j] ) {
				tmp_cnt ++;
				if( cur_a + tmp_cnt == gol ) {
					write_ans( i, j );
					return 0;
				}
			}
		}
		cur_a += tmp_cnt;
	}

	fclose( stdin );
	fclose( stdout );
	return 0;
}
