// Woshiluo<woshiluo@woshiluo.site>
// 2020/09/08 22:44:14 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <bitset>
#include <vector>
#include <algorithm>

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }

int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

const int N = 1e3 + 1e2;

int T;
int n;
int a[N];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		std::bitset<N> vis;
		std::vector<int> ans;
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		vis[n] = 1;
		ans.push_back( a[n] );

		int current_gcd = a[n];
		for( int _o = 2; _o <= n; _o ++ ) {
			int max_gcd = 0, max_gcd_id = 0;
			for( int i = 1; i <= n; i ++ ) {
				if( vis[i] ) 
					continue;
				if( gcd( current_gcd, a[i] ) > max_gcd ) {
					max_gcd = gcd( current_gcd, a[i] );;
					max_gcd_id = i;
				}
			}
			vis[max_gcd_id] = true;
			ans.push_back( a[max_gcd_id] );
			current_gcd = max_gcd;
		}
		
		int size = ans.size();
		for( int i = 0; i < size; i ++ ) {
			printf( "%d ", ans[i] );
		}
		printf( "\n" );
	}
}
