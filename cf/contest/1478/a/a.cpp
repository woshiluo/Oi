// Woshiluo<woshiluo@woshiluo.site>
// 2021/01/28 22:35:45 
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


int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		int n;
		scanf( "%d", &n );
		int max_cnt = 0, la = -1, cnt = 0;
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%d", &tmp );
			if( tmp == la ) 
				cnt ++;
			else {
				chk_Max( max_cnt, cnt );
				la = tmp;
				cnt = 1;
			}
		}
		chk_Max( max_cnt, cnt );
		printf( "%d\n", max_cnt );
	}
}
