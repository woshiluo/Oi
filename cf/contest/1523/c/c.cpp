// Woshiluo<woshiluo@woshiluo.site>
// 2021/05/30 22:45:41 
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

const int N = 1e4 + 1e3;

int T;
int n;
int a[N];

void print( int depth ) {
	for( int i = 1; i <= depth; i ++ ) {
		printf( "%d%c", a[i], i == depth? '\n': '.' );
	}
}

void dfs( int cur, int depth );
void find( int cur, int depth );

void find( int cur, int depth ) {
	if( a[ depth + 1 ] + 1 == cur ) {
		a[ depth + 1 ] = cur;
		dfs( cur, depth + 1 );
	}
	else
		find( cur, depth - 1 );
}
void dfs( int cur, int depth ) {
	if( depth != 0 ) 
		print(depth);
	if( n == 0 ) 
		return ;
	n --;
	int tmp = read<int>();
	if( tmp == cur + 1 ) {
		a[depth] = tmp;
		dfs( tmp, depth );
	}
	else if( tmp == 1 ) {
		a[ depth + 1 ] = 1;
		dfs( tmp, depth + 1 );
	}
	else {
		find( tmp, depth - 1 );
	}
}

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	T = read<int>();
	while( T -- ) {
		n = read<int>();
		dfs( N + 10, 0 );
	}
}
