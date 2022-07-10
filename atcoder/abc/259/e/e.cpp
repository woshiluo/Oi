/*
 * e.cpp
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

#include <set>
#include <map>
#include <unordered_map>
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

struct Node { int p, e; };

std::vector<Node> nodes[N];
std::unordered_map<int, std::vector<int>> mp;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		cint m = read<int>();
		for( int j = 1; j <= m; j ++ ) {
			cint p = read<int>();
			cint c = read<int>();
			nodes[i].push_back( (Node) { p, c } );
			mp[p].push_back(c);
		}
	}

	for( auto &pair: mp ) 
		std::sort( pair.second.begin(), pair.second.end() );
	
	int res = 0;
	bool does_nothing = false;
	for( int i = 1; i <= n; i ++ ) {
		bool flag = false;
		for( auto &pair: nodes[i] ) {
			cint p = pair.p;
			cint e = pair.e;
			auto &cmp = mp[p];
			if( cmp.size() == 1 || ( cmp.back() == e && cmp.back() != cmp[ cmp.size() - 2 ] ) ) {
				flag = true;
				break;
			}
		}
		res += flag;
		if( !flag ) 
			does_nothing = true;
	}

	printf( "%d\n", res + does_nothing );
}
