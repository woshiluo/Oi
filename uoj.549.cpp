#include <cstdio>
#include <cstring>

inline void chk_Min( int &a, int b ) { if( a > b ) a = b; }

const int N = 6e5 + 1e4;
const int INF = 0x3f3f3f3f;

int n, k;
int a[N], sum[N], pow[30];
int min[2][ 1 << 20 ][10];

int main() {
#ifdef woshiluo
	freopen( "uoj.549.in", "r", stdin );
	freopen( "uoj.549.out", "w", stdout );
#endif
	pow[0] = 1;
	for( int i = 1; i <= 20; i ++ ) {
		pow[i] = pow[ i - 1 ] * 2;
	}

	scanf( "%d%d", &n, &k );
	int p1 = 0;
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		while( a[i] >= pow[p1] ) 
			p1 ++;
	}
	int max_a_i = pow[p1];

	sum[1] = a[1];
	for( int i = 2; i <= n; i ++ ) {
		sum[i] = sum[ i - 1 ] ^ a[i];
	}
	
	memset( min, INF, sizeof(min) );
	int cur = 1, lst = 0;
	min[cur][0][0] = 0;
	for( int i = 1; i <= n; i ++ ) {
		cur ^= 1; lst ^= 1;
		memcpy( min[cur], min[lst], sizeof(min[cur]) );
		for( int j = 1; j <= k; j ++ ) {
			for( int o = 0; o < max_a_i; o ++ ) {
				chk_Min( min[cur][ sum[i] ][j], min[lst][o][ j - 1 ] + ( sum[i] ^ o ) );			
			}
		}
		if( i >= k ) {
			int res = INF;
			for( int o = 0; o < max_a_i; o ++ ) {
				chk_Min( res, min[cur][o][k] );
			}
			printf( "%d ", res );
		}
	}
}
