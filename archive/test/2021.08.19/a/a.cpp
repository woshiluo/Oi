/*
 * a.cpp
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
	for (; !isdigit(ch); ch = getchar())
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

const int N = 1e6 + 1e5;
const int BIT = 35;

int pow_2[BIT];
std::map<int, int> mp;
std::vector<int> bit[BIT];

int highbit( int cur ) {
	if( cur == 0 ) 
		return 0;
	for( int i = 30; i >= 0; i -- ) {
		if( cur & pow_2[i] ) 
			return i + 1;
	}
}

int main() {
	{
		int tmp = 1;
		for( int i = 0; i <= 30; i ++ ) {
			mp[ tmp ] = i;
			pow_2[i] = tmp;
			tmp <<= 1;
		}
	}
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		int tmp = read<int>();
		bit[ highbit(tmp) ].push_back(tmp);
	}
	for( int i = 0; i < BIT; i ++ ) 
		std::sort( bit[i].begin(), bit[i].end() );

	int p1 = BIT - 1, ans = 0, res = 0;
	for( int i = 1; i <= n; i ++ ) {
		while( bit[p1].size() == 0 && p1 > 0 ) 
			p1 --;

		if( p1 < 0 ) {
			ans += res; 
			continue;
		}

		res |= bit[p1].back();
		ans += res;

		int size = bit[p1].size();
		for( int i = 0; i < size - 1; i ++ ) {
		}

		p1 --;
	}
}
