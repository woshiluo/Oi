// Woshiluo<woshiluo@woshiluo.site>
// 2021/02/28 21:35:28 
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
template <typename T=int>
T read() { 
	T sum = 0, fl = 1; 
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

const int N = 1e5 + 1e4;

int a[N * 10];
int cnt[N];

int main() {
	int n, q;
	scanf( "%d%d", &n, &q );

	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &a[i] );
		cnt[ a[i] ] ++;
	}

	while( q -- ) {
		int type, x;
		scanf( "%d%d", &type, &x );

		if( type == 1 ) {
			cnt[ a[x] ] --;
			a[x] ^= 1;
			cnt[ a[x] ] ++;
		}
		else {
			if( x <= cnt[1] ) 
				printf( "1\n" );
			else 
				printf( "0\n" );
		}
	}
}
