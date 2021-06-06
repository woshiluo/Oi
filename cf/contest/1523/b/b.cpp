// Woshiluo<woshiluo@woshiluo.site>
// 2021/05/30 22:59:17 
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



int main() {
	int T;
	T = read<int>();
	while( T -- ) {
		int n;
		n = read<int>();
		for( int i = 1; i <= n; i ++ ) 
			int tmp = read<int>();

		printf( "%d\n", ( n >> 1 ) * 6 );
		for( int i = 1; i <= ( n >> 1 ); i ++ ) {
			int base = ( ( i - 1 ) << 1 ) + 1;
			printf( "1 %d %d\n", base, base + 1 );
			printf( "1 %d %d\n", base, base + 1 );
			printf( "2 %d %d\n", base, base + 1 );
			printf( "1 %d %d\n", base, base + 1 );
			printf( "1 %d %d\n", base, base + 1 );
			printf( "2 %d %d\n", base, base + 1 );
		}
	}
}
