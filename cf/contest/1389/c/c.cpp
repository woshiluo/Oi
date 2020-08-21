// Woshiluo<woshiluo@woshiluo.site>
// 2020/07/29 23:01:11 
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

const int N = 2e5 + 1e4;

int T, len;
char s[N];

int check( char fir, char lst ) {
	int res = 0;
	bool cur = true;
	for( int i = 0; i < len; i ++ ) {
		if( cur && s[i] == fir ) {
			cur = false;
			continue;
		}
		else if( cur == false && s[i] == lst ){
			cur = true;
			continue;
		}
		res ++;
	}

	if( cur || fir == lst )
		return res;
	return len;
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	scanf( "%d", &T );
	while( T -- ) {
		scanf( "%s", s );
		len = strlen(s);
		int ans = len;
		for( int i = '0'; i <= '9'; i ++ ) {
			for( int j = '0'; j <= '9'; j ++ ) {
				ans = Min( ans, check( i, j ) );
			}
		}
		printf( "%d\n", ans );
	}
}
