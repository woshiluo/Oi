#include <cstdio>

const int N = 3e6 + 1e5;
const int M = 512;

int w_len, s_len;
char w[N], s[N];
int pool_w[M], pool_s[M];

int main() {
#ifdef woshiluo
	freopen( "writing.in", "r", stdin );
	freopen( "writing.out", "w", stdout );
#endif
	scanf( "%d%d", &w_len, &s_len );
	scanf( "%s", w + 1 );
	scanf( "%s", s + 1 );
	for( int i = 1; i <= w_len; i ++ ) {
		pool_w[ w[i] ] ++;
	}
	int ans = 0, cur_cnt = 0;
	for( int i = 1; i <= s_len; i ++ ) {
		if( i > w_len ) {
			int p = i - w_len;
			if( pool_w[ s[p] ] && pool_s[ s[p] ] <= pool_w[ s[p] ] )
					cur_cnt --;
			pool_s[ s[p] ] --;
		}
		if( pool_w[ s[i] ] ) {
			if( pool_s[ s[i] ] < pool_w[ s[i] ] ) {
				cur_cnt ++;
			}
			pool_s[ s[i] ] ++;
		}
		if( i >= w_len && cur_cnt == w_len ) 
			ans ++;
	}
	printf( "%d\n", ans );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
