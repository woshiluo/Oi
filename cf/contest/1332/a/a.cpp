// Woshiluo<woshiluo@woshiluo.site>
// Started at 2020/03/31 21:41:28
// Blog: https://blog.woshiluo.com
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>

template<class T> 
T Min( T a, T b ) { return a < b? a: b; }
template<class T> 
T Max( T a, T b ) { return a > b? a: b; }
template<class T> 
void chk_Min( T &a, T b ) { if( a > b ) a = b; }
template<class T> 
void chk_Max( T &a, T b ) { if( a < b ) a = b; }

int T;
int a, b, c, d;
int st, ed, lx, ly, rx, ry;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d%d%d", &a, &b, &c, &d );
		scanf( "%d%d%d%d%d%d", &st, &ed, &lx, &ly, &rx, &ry );
		if( a > b ) {
			 int tmp = a - b;
			 if( rx - st < tmp )
				 flag = false;
		}
		if( b > a ) {
			 int tmp = b - a;
			 if( st - lx < tmp )
				 flag = false;
		}
		if( c > d ) 

	}
}
