/*
 * b.cpp 2023-08-25
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

int main() {
#ifdef woshiluo
	freopen( "b.in", "r", stdin );
	freopen( "b.out", "w", stdout );
#endif

	int T = read<int>();
	while( T -- ) {
		int n = read<int>();
		std::vector<int> nums;
		while( n ) {
			nums.push_back( n & 1 );
			n >>= 1;
		}
		bool flag = true;
		std::reverse( nums.begin(), nums.end() );
		std::vector<int> ops;
		cint size = nums.size();
		for( int i = 1; i < size; i ++ ) {
			if( nums[i] == 1 ) {
				if( nums[ i - 1 ] == 0 ) 
					ops.push_back(1);
				else
					ops.push_back(2);
			}
			else {
				if( nums[ i - 1 ] == 0 ) 
					ops.push_back(1);
				else
					ops.push_back(2);
			}
		}
		if( nums.back() == 0 ) 
			flag = false;

		if( !flag ) 
			printf( "-1\n" );
		else {
			printf( "%lu\n", ops.size() );
			for( auto &x: ops ) 
				printf( "%d ", x );
			printf( "\n" );
		}
	}
}
