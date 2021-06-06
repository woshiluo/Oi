// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/04 23:36:50 
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

const int N = 2e5 + 1e4;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		char str[N];
		scanf( "%s", str + 1 );
		int len = strlen(str + 1);
		ll ans = 0;
		int st = 1, la_0 = 0, la_1 = 0;
		for( int i = 1; i <= len; i ++ ) {
			if( str[i] == '0' ) {
				if( la_0 != 0 && ( i - la_0 - 1 ) % 2 == 0 ) 
					st = std::max( st, la_0 + 1 );
				if( la_1 != 0 && ( i - la_1 - 1 ) % 2 == 1 ) 
					st = std::max( st, la_1 + 1 );
				la_0 = i;
			}
			if( str[i] == '1' ) {
				if( la_1 != 0 && ( i - la_1 - 1 ) % 2 == 0 ) 
					st = std::max( st, la_1 + 1 );
				if( la_0 != 0 && ( i - la_0 - 1 ) % 2 == 1 ) 
					st = std::max( st, la_0 + 1 );
				la_1 = i;
			}
			ans += ( i - st + 1 );
		}
		printf( "%lld\n", ans );
	}
}
