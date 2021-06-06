// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/04 23:28:15 
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


int gcd( int a, int b ) { return b? gcd( b, a % b ): a; }

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		std::vector<int> odd, even, a;
		int n = read<int>();
		for( int i = 1; i <= n; i ++ ) {
			int tmp = read<int>();
			if( tmp & 1 ) 
				odd.push_back(tmp);
			else 
				even.push_back(tmp);
		}
		for( auto tmp: even ) 
			a.push_back(tmp);
		for( auto tmp: odd ) 
			a.push_back(tmp);

		int size = a.size(), cnt = 0;
		for( int i = 0; i < size; i ++ ) {
			for( int j = i + 1; j < size; j ++ ) {
				cnt += ( gcd( a[i], a[j] << 1 ) > 1 );
			}
		}

		printf( "%d\n", cnt );
	}
}
