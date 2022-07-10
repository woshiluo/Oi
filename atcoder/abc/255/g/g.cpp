/*
 * g.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

#include <map>
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

const int N = 2e5 + 1e4;

ll a[N];

std::vector<int> blocks;
std::map<ll, std::vector<ll>> list;
std::map<ll, ll> sg;

ll get_sg( const ll cur ) {
	if( sg.count(cur) )
		return sg[cur];

	std::sort( list[cur].begin(), list[cur].end() );
	while( list[cur].back() > cur ) 
		list[cur].pop_back();
	std::reverse( list[cur].begin(), list[cur].end() );
	if( list[cur].size() == 0 ) {
		cint pos = std::lower_bound( blocks.begin(), blocks.end(), cur ) - blocks.begin() - 1;
		sg[cur] = cur - pos + 1;
		return sg[cur];
	}
	else {
		return sg[cur] = get_sg( cur - list[cur].front() );
	}

	return sg[cur] = cur;
}

int main() {
	cint n = read<int>();
	cint m = read<int>();

	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<ll>();
	}
	for( int i = 1; i <= m; i ++ ) {
		cint x = read<ll>();
		cint y = read<ll>();
		list[x].push_back(y);
	}

	for( int i = 1; i <= n; i ++ ) {
		a[i] = get_sg( a[i] );
	}
}
