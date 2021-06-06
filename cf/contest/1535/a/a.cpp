// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/04 23:23:49 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <iostream>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

template <class T> 
T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
T Min( T a, T b ) { return a < b? a: b; }
template <class T> 
void chk_Max( T &a, T b ) { if( b > a ) a = b; }
template <class T> 
void chk_Min( T &a, T b ) { if( b < a ) a = b; }
template <typename T>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

bool check( int a, int b, int c, int d ) { 
	if( a == c && b == d ) 
		return true;
	if( a == d && b == c ) 
		return true;
	return false;
}

int main() {
	int T = read<int>();
	while( T -- ) {
		int s[4], a[4];
		for( int i = 0; i < 4; i ++ ) {
			scanf( "%d", &s[i] );
			a[i] = s[i];
		}
		std::sort( a, a + 4 );
		if( check( std::max( s[0], s[1] ), std::max( s[2], s[3] ) 
					, a[2], a[3] ) ) 
			printf( "YES" );
		else
			printf( "NO" );
		printf( "\n" );
	}
}
