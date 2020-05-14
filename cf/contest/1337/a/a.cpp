// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/15 22:38:00 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

int T;
int a, b, c, d;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d%d", &a, &b, &c, &d );
		if( a + b > c ) {
			printf( "%d %d %d", a, b, c );
		}
		else {
			int tmp = a + b;
			tmp = c - tmp + 1;
			if( a + tmp <= b ) 
				a += tmp;
			else if( b + tmp <= c ) 
				b += tmp;
			else {
				a = b;
				tmp = c - ( b + b ) + 1;
				b += tmp;
			}
			printf( "%d %d %d", a, b, c );
		}
		printf( "\n" );
	}
}
