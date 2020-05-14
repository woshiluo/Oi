// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/12 22:19:56 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

const int N = 1e5 + 1e4;

int T;
int n;
int a[N];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
		}
		std::sort( a + 1, a + n + 1 );
		bool flag = true;
		int p1 = 1, p2 = n;
		std::vector<int> out;
		while( p1 <= p2 ) {
			if( flag ) {
				out.push_back( a[p1] );
				p1 ++;
			}
			else {
				out.push_back( a[p2] );
				p2 --;
			}
			flag = ( flag == false );
		}
		for( int i = n - 1; i >= 0; i -- ) {
			printf( "%d ", out[i] );
		}
		printf( "\n" );
	}
}
