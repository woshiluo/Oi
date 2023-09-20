#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

typedef long long ll;

const int N = 510;
const int INF = 0x3f3f3f3f;
const ll LNF = 0x3f3f3f3f3f3f3f3f;

inline void chk_Min( ll &a, ll b ) { a = std::min( a, b ); }
ll cost( ll a ) {
	return a * (ll)sqrt(a);
}

int n;
int a[N];
ll pre[N][N], suf[N][N], f[N][N];

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
	}

	memset( f, INF, sizeof(f) );
	memset( pre, INF, sizeof(pre) );
	memset( suf, INF, sizeof(suf) );

	pre[0][1] = suf[0][n] = 0;
	for( int t = 1; t <= n; t ++ ) {
		for( int i = 1; i <= n; i ++ ) {
			f[t][i] = f[ t - 1 ][i];
			if( i == 1 ) 
				pre[t][i] = 0;
			else {
				pre[t][i] = pre[ t - 1 ][i];
				for( int j = 1; j <= i; j ++ ) {
					chk_Min( pre[t][i], pre[ t - 1 ][j] + cost( a[i] - a[j] ) );
				}
			}
			if( i == n ) 
				suf[t][i] = 0;
			else {
				suf[t][i] = suf[ t - 1 ][i];
				for( int j = n; j >= i; j --  ) {
					chk_Min( suf[t][i], suf[ t - 1 ][j] + cost( a[j] - a[i] ) );
				}
			}

			{
				int p = i;
				for( int j = i - 1; j; j -- ) {
					while( p < n && a[ p + 1 ] - a[i] <= a[i] - a[j] ) 
						p ++;
					chk_Min( f[t][i], 
							cost( a[i] - a[j] ) +
							suf[ t - 1 ][p] + pre[ t - 1 ][j] );
					chk_Min( f[t][i],
							f[ t - 1 ][j] + cost( a[i] - a[j] ) );
				}
			}
			{
				int p = i;
				for( int j = i; j <= n; j ++ ) {
					while( p > 1 && a[i] - a[ p - 1 ] <= a[j] - a[i] ) 
						p --;
					chk_Min( f[t][i], 
							cost( a[j] - a[i] ) +
							suf[ t - 1 ][j] + pre[ t - 1 ][p] );
					chk_Min( f[t][i],
							f[ t - 1 ][j] + cost( a[j] - a[i] ) );
				}
			}
		}
	}

	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j < n; j ++ ) {
			printf( "%lld ", f[j][i] );
		}
		printf( "\n" );
	}
}
