#include <cstdio>
#include <cstring>

const int N = 1 << 22;

const int mod = 1e9 + 7;

int n, k;
int a[N];
bool vis[N];

int f( int x ) {
	int cur_x = 1, res = 0;
	for( int i = 0; i < k; i ++ ) {
		res = ( res + ( 1LL * cur_x * a[i] ) % mod ) % mod;
		cur_x = ( 1LL * cur_x * x ) % mod;
	}
	return res;
}

int main() {
	freopen( "angry.in", "r", stdin );
	freopen( "angry.out", "w", stdout );

	{
		char tmp[N];
		scanf( "%s", tmp + 1 );
		n = strlen( tmp + 1 );
		int res = 0;
		for( int i = 1; i <= n; i ++ ) {
			res <<= 1;
			res |= ( tmp[i] - '0' );
		}
		n = res;
	}
	scanf( "%d", &k );
	for( int i = 0; i < k; i ++ ) {
		scanf( "%d", &a[i] );
	}
	int pow_2 = 1, ans = 0;
	vis[0] = false; vis[1] = true;
	for( int o = 0; ( pow_2 << 1 ) < N; o ++, pow_2 <<= 1 ) {
		for( int i = pow_2; i <= ( pow_2 << 1 ); i ++ ) {
			if( i >= n ) 
				break;
			vis[i] = vis[ i - pow_2 ] ^ 1;
			if( vis[i] ) 
				ans = ( ans + f(i) ) % mod;
		}
	}

	printf( "%d\n", ( ans + mod ) % mod );

	fclose( stdin );
	fclose( stdout );
	return 0;
}
