// Woshiluo<woshiluo@woshiluo.site>
// 2021/05/31 00:05:42 
// Blog: https://blog.woshiluo.com

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

const int N = 1e3 + 1e2;

int n, m;
int a[N], b[N];

void gen() {
	for( int i = 2; i < n; i ++ ) {
		b[i] = a[i];
		b[i] |= ( a[ i - 1 ] + a[ i + 1 ] ) & 1;
	} 
	b[1] = a[1] || a[2];
	b[n] = a[n] || a[ n - 1 ];
	for( int i = 1; i <= n; i ++ ) 
		a[i] = b[i];
}

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		memset( a, 0, sizeof(a) );

		n = read<int>(); m = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			int tmp;
			scanf( "%1d", &a[i] );
		}
		m = Min( n, m );
		for( int i = 1; i <= m; i ++ ) 
			gen();
		for( int i = 1; i <= n; i ++ ) {
			printf( "%d", a[i] );
		}
		printf( "\n" );
	}
}
