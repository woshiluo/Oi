// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/21 23:07:42 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }


const int N = 1e5 + 1e4;

int T;
int n;
int a[N], b[N], id[N];

inline int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		int cnt[N];
		std::queue<int> q[N];
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			if( mp.count(a[i]) == 0 ) {
				cnt ++;
				mp[ a[i] ] = cnt;
			}
				
			q[ mp[ a[i] ] ].push(i);
			b[i] = a[i];
		}
		std::sort( b + 1, b + n + 1 );

		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			if( a[i] != b[i] ) {
				int lst = a[i];
				if( cnt[ mp[ a[i] ] ] >= 0 ) {
					cnt[ mp[ a[i] ] ] == 0;
					lst = la[ mp[ a[i] ] ];
				}
				if( gcd( a[i], b[i] ) != b[1] ) {
					flag = true;
					break;
				}
				else {
					cnt[ mp[ b[i] ] ] ++;
				}
			}
			else 
				q[ a[i] ].pop();
		}
		
		printf( "%s\n", flag? "NO": "YES" );
	}
}
