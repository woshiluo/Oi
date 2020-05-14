// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/26 22:45:39 
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
char t[1100], s[1100];

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%s", t );
		int n = strlen(t);
		int len = 0;
		int cur = t[0] - '0', p1 = 0;
		bool flag = false;
		if( n == 1 ) {
			printf( "%s\n", t );
			continue;
		}
		for( int i = 1; i < n; i ++ ) {
			if( t[i] != t[ i - 1 ] ) 
				flag = true;
		}
		if( flag == false ) {
			printf( "%s\n", t );
			continue;
		}
		while( p1 < n ) {
			s[len] = cur + '0';
			len ++;
			if( t[p1] == cur + '0' ) {
				p1 ++;
			} 
			cur = cur ^ 1;
		}
		s[len] = 0;
		printf( "%s\n", s );
	}
}
