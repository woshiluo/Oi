// Woshiluo<woshiluo@woshiluo.site>
// 2020/04/26 22:38:07 
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
T aabs( T a ) { return a < 0? -a: a; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }


int T;
int a, b, x, y;

int main() {
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%d%d", &x, &y );
		scanf( "%d%d", &a, &b );
		if( x > y ) 
			std::swap( x, y );
		if( y < 0 ) 
			x = -a, y = -b;
		if( x > 0 && b < 2LL * a ) {
			int tmp = y - x;
			printf( "%lld\n", 1LL* x * b + 1LL * tmp * a );
		}
		else {
			printf( "%lld\n", 1LL * ( aabs(x) + aabs(y) ) * a );
		}
	}

}
