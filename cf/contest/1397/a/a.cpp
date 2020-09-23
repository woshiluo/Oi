// Woshiluo<woshiluo@woshiluo.site>
// 2020/08/30 22:37:13 
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

int T;
int n;
char a[1100];
int sum[200];

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		memset( sum, 0, sizeof(sum) );
		scanf( "%d", &n );
		for( int i = 1; i <= n; i ++ ) {
			scanf( "%s", a );
			int len = strlen(a);
			for( int i = 0; i < len; i ++ ) {
				sum[ a[i] ] ++;
			}
		}
		bool flag = true;
		for( int i = 'a'; i <= 'z'; i ++ ) {
			if( sum[i] % n != 0 ) {
				flag = false;
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
