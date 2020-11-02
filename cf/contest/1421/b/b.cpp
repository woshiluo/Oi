// Woshiluo<woshiluo@woshiluo.site>
// 2020/10/18 17:13:14 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

const int N = 510;

int n;
inline bool check( int cur ) { return ( cur >= 1 && cur <= n ); }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int mp[N][N];
		for( int i = 1; i <= n; i ++ ) {
			char s[N];
			scanf( "%s", s + 1 );
			for( int j = 1; j <= n; j ++ ) {
				if( s[j] == 'S' || s[j] == 'F' )
					mp[i][j] = 0;
				else
					mp[i][j] = ( s[j] - '0' );
			}
		}
		int f[N], sum[N];
		int ed = n + n;
		for( int i = 3; i < ed; i ++ ) {
			sum[i] = 0;
			int res = 0;
			for( int x = 1; x <= n; x ++ ) {
				int y = i - x;
				if( check(x) && check(y) ) {
					sum[i] ++;
					res += mp[x][y];
				}
			}
			f[i] = res;
		}

		bool flag = false;
		for( int i = 3; i < ed; i ++ ) {
			for( int j = 3; j < ed; j ++ ) {
				if( i == j ) 
					continue;
				if( f[i] + ( sum[j] - f[j] ) <= 2 ) {
					flag = true;
					printf( "%d\n", f[i] + sum[j] - f[j] );
					for( int x = 1; x <= n; x ++ ) {
						int y = i - x;
						if( check(x) && check(y) && mp[x][y] ) {
							printf( "%d %d\n", x, y );
						}
					}
					for( int x = 1; x <= n; x ++ ) {
						int y = j - x;
						if( check(x) && check(y) && mp[x][y] == 0 ) {
							printf( "%d %d\n", x, y );
						}
					}
					break;
				}
			}
			if( flag ) 
				break;
		}
	}
}
