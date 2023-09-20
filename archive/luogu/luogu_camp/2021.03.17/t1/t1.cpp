#include <cstdio>

const int N = 2e3 + 1e2;
const int mod = 1e9 + 7;

typedef long long ll;

int n, m, tot_black; 
int mp[N][N], row_cnt[N], row[N][N];
ll dis[N][N];

inline long long ksm( long long a, int p ) {
	int res = 1;
	while( p ) { 
		if( p & 1 ) 
			res = ( 1LL * res * a ) % mod;
		a = ( 1LL * a * a ) % mod;
		p >>= 1;
	}
	return res;
}

int main() {
#ifdef woshiluo
	freopen( "t1.in", "r", stdin );
	freopen( "t1.out", "w", stdout );
#endif
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			scanf( "%1d", &mp[i][j] );
			tot_black += mp[i][j];
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		int cur_dis = 0, cnt = 0, right_cnt;

		for( int j = 1; j <= m; j ++ ) {
			if( mp[i][j] ) {
				cur_dis += ( j - 1 );
				cnt ++;
			}
		}

		row_cnt[i] = cnt;
		right_cnt = cnt;

		for( int j = 1; j <= m; j ++ ) {
			right_cnt -= mp[i][j];
			row[i][j] = cur_dis;
			cur_dis += ( cnt - right_cnt );
			cur_dis -= right_cnt;
		}
	}

	for( int j = 1; j <= m; j ++ ) {
		int cnt = 0, bottom_cnt;
		ll res = 0;
		for( int i = 1; i <= n; i ++ ) {
			cnt += row_cnt[i];
			res += row[i][j] + ( row_cnt[i] * ( i - 1 ) );
		}

		bottom_cnt = cnt;
		for( int i = 1; i <= n; i ++ ) {
			bottom_cnt -= row_cnt[i];

			dis[i][j] = res;

			res += cnt - bottom_cnt;
			res -= bottom_cnt;
		}
	}

	long long ans = 0, black_inv = ksm( tot_black, mod - 2 );
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= m; j ++ ) {
			ans ^= ( 1LL * dis[i][j] * black_inv ) % mod;
		}
	}
	printf( "%lld\n", ans );
}
