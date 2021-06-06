// Woshiluo<woshiluo@woshiluo.site>
// 2021/06/05 21:13:06 
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

int n, k;
std::mp<int, std::vector<char*>> mp;

bool cmp( char* _a, char* _b ) {
}

void solve() {
	for( auto node: mp ) {
	}
}

int main() {
	scanf( "%d", &n );
	char tmp[N];
	scanf( "%s", tmp );
	k = strlen(tmp);
	char a[ n + 10 ][ k + 10 ];
	for( int i = 0; i < k; i ++ ) 
		a[1][i] = tmp[i];

	for( int i = 2; i <= n; i ++ ) {
		scanf( "%s", a[i] );
	}

	for( int i = 1; i <= n; i ++ ) {
		mp[ hash( a[i] ) ].push_back( a[i] );
	}
}
