/*
 * e.cpp
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

const int N = 5e5 + 1e4;

struct Set {
	int fa[N];
	Set( int max = 1 ) {
		for( int i = 0; i <= max; i ++ ) {
			fa[i] = i;
		}
	}
	inline int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int *p = &get_fa(fa[cur]);
	//	fa[cur] = *p;
		return *p;
	}
	inline int& operator[] ( int cur ) {
		return get_fa(cur);
	}
};

struct Node { int idx, x, y; };

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int q = read<int>();
	std::vector<int> num, ans;
	std::vector<Node> op;
	Set set( N - 1 );
	while( q -- ) {
		int cop;
		cop = read<int>(); 
		if( cop == 1 ) 
			num.push_back( read<int>() );
		else {
			int x, y; 
			x = read<int>(); y = read<int>();
			op.push_back( (Node) { num.size(), x, y } );
		}
	}
	// std::reverse( op.begin(), op.end() );
	int len = num.size(), p = op.size() - 1;
	for( int i = len - 1; i >= 0; i -- ) {
		while( p >= 0 && op[p].idx >= i + 1 ) {
			set.fa[ op[p].x ] = op[p].y;
			p --;
		}
		ans.push_back( set[ num[i] ] );
	}
	std::reverse( ans.begin(), ans.end() );
	for( auto &cur: ans ) 
		printf( "%d ", cur );
}
