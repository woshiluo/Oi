// Woshiluo<woshiluo@woshiluo.site>
// 2020/12/01 14:34:04 
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
	while( T -- )  {
		int a;
		scanf( "%d", &a );
		int cur = 0, p = 1, ans = 0;
		while( cur < a ) {
			cur += p;
			p ++;
			ans ++;
		}
		int less = ( cur - a );
		printf( "%d\n", ans + ( less == 1 ) );
	}
}
