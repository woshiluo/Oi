/*
 * k.cpp 2023-09-26
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
#include <algorithm>

typedef const int cint;
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

const int N = 1e5 + 1e4;

int a[N];

int main() {
#ifdef woshiluo
	freopen( "k.in", "r", stdin );
	freopen( "k.out", "w", stdout );
#endif

	cint n = read<int>();
	std::vector<int> nums;
	nums.push_back(0);
	nums.push_back(1);
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
		nums.push_back( a[i] );
		nums.push_back( a[i] + 1 );
		nums.push_back( ( ( a[i] ) / 2 ) );
		nums.push_back( ( ( a[i] ) / 2 ) + 1 );
	}
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	auto find_num = [&]( cint cur ) { return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1; };
	std::vector<int> sum( nums.size() + 5 );
	for( int i = 1; i <= n; i ++ ) {
		sum[ find_num( a[i] ) ] ++;
		sum[ find_num( a[i] + 1 ) ] --;
		sum[0] ++;
		sum[ find_num( ( ( a[i]  ) / 2 ) + 1 ) ] --;
	}
	cint size = sum.size();
	for( int i = 1; i < size; i ++ ) 
		sum[i] += sum[ i - 1 ];
	for( int i = size - 1; i >= 1; i -- ) {
		if( sum[i] == n ) {
			printf( "%d\n", nums[ i - 1 ] );
			return 0;
		}
	}
}
