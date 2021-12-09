/*
 * loj.2084.cpp
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

#include <map>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
T aabs( T a ) { return a > 0? a: -a; }
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

int n, m, c;
std::map<int, std::map<int, bool>> mp;

struct Node {
	int x, y;
};
inline int dis( Node _a, Node _b ) { return aabs( _a.x - _b.x ) + aabs( _a.y - _b.y ); }

bool is_possible() {
	if( n * m <= c + 1 ) 
		return false;
	else if( n * m == c + 2 ) {
		std::vector<Node> tmp;
		for( int i = 1; i <= n; i ++ ) {
			for( int j = 1; j <= m; j ++ ) {
				if( mp[i].count(j) ) 
					continue;
				else 
					tmp.push_back( (Node) { i, j } );
			}
		}
		if( tmp.size() == 2 && dis( tmp[0], tmp[1] ) )
			return false;
	}
	return true;
}

inline int check() {
	std::vector<Node> need;
}

int get_ans() {
}

int main() {
	int T = read<int>();
	while( T -- ) {
		mp.clear();
		n = read<int>(); m = read<int>(); c = read<int>();

		for( int i = 1; i <= c; i ++ ) {
			int x, y;
			x = read<int>(); y = read<int>();
			mp[x][y] = true;
			if( is_possible() ) 
				printf( "%d\n", get_ans() );
			else 
				printf( "-1\n" );
		}
	}
}
