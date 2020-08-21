// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/21 23:50:08 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

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


int T;
int n;

int main() {
#ifdef woshiluo
	freopen( "c2.in", "r", stdin );
	freopen( "c2.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		std::vector<int> ans[2];
		scanf( "%d", &n );
		int la_0 = 0, la_1 = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp; 
			scanf( "%1d", &tmp );
			if( tmp == 0 ) {
				if( la_1 ) {
					if( la_0 )
						ans[0].push_back(la_0);
					ans[0].push_back(la_1);
				}
				la_1 = 0;
				la_0 = i;
			}
			else 
				la_1 = i;
		}
		if( la_1 ) {
			if( la_0 ) 
				ans[0].push_back(la_0);
			ans[0].push_back(la_1);
		}

		la_0 = 0, la_1 = 0;
		for( int i = 1; i <= n; i ++ ) { 
			int tmp; 
			scanf( "%1d", &tmp );
			if( tmp == 0 ) {
				if( la_1 ) {
					if( la_0 ) 
						ans[1].push_back(la_0);
					ans[1].push_back(la_1);
				}
				la_1 = 0;
				la_0 = i;
			}
			else 
				la_1 = i;
		}
		if( la_1 ) {
			if( la_0 ) 
				ans[1].push_back(la_0);
			ans[1].push_back(la_1);
		}

		int size1 = ans[0].size(), size2 = ans[1].size();
		printf( "%d ", size1 + size2 );
		for( int i = 0; i < size1; i ++ ) 
			printf( "%d ", ans[0][i] );
		for( int i = size2 - 1; i >= 0; i -- ) 
			printf( "%d ", ans[1][i] );
		printf( "\n" );
	}
}
