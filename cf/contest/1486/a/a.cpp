// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/18 22:38:27 
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

bool work() {
	int n;
	scanf( "%d", &n );
	long long buf = 0;
	bool flag = true;
	for( int i = 0; i < n; i ++ ) {
		long long tmp;
		scanf( "%lld", &tmp );
		if( tmp > i ) 
			buf += ( tmp - i );
		else {
			buf -= ( i - tmp );
		}

		if( buf < 0 ) 
			flag = false;
	}
	return flag;
}

int main() {
	int T;
	scanf( "%d", &T );
	while( T -- ) {
		printf( "%s\n", work()? "YES": "NO" );
	}
}
