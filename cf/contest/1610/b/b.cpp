/*
 * b.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
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
	for (; isdigit(ch) == 0; ch = getchar())
		if (ch == '-') fl = -1;
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}
template <class T> 
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 2e5 + 1e4;

int n;
int a[N];
std::vector<int> pos[N];

bool check( int _a[], int cur ) {
	std::vector<int> b;
	for( int i = 1; i <= n; i ++ )
		if( a[i] != cur )
			b.push_back( a[i] );
	int size = b.size();
	for( int i = 0; i < size; i ++ ) {
		if( b[i] != b[ size - 1 - i ] )
			return false;
	}
	return true;
}

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		n = read<int>();
		bool flag = false;
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			pos[ a[i] ].push_back(i);
		}
		flag = ( flag || check( a, 0 ) );
		flag = ( flag || check( a, a[1] ) );
		int rig = n;
		for( int i = 1; i <= n; i ++ ) {
			if( pos[ a[i] ].size() == 1 ) {
				flag = ( flag || check( a, a[i] ) );
				break;
			}
			int lst = pos[ a[i] ].back(); pos[ a[i] ].pop_back();
			if( lst == rig )
				rig --;
			else {
				flag = ( flag || check( a, a[ lst + 1 ] ) );
				flag = ( flag || check( a, a[lst] ) );
				break;
			}
		}
		printf( "%s\n", flag? "YES": "NO" );
	}
}
