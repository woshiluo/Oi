/*
 * c.cpp
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

const int N = 1e5 + 1e4;


struct Node {
	int res, pos;
};
std::vector<int> a[N];

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		int n = read<int>();

		for( int i = 1; i <= n; i ++ ) {
			int k = read<int>();
			for( int j = 1; j <= k; j ++ ) {
				int tmp = read<int>();
				a[i].push_back(tmp);
			}
		}
		
		std::vector<Node> list;
		for( int i = 1; i <= n; i ++ ) {
			int res = a[i].front(), size = a[i].size();
			for( int j = 0; j < size; j ++ ) {
				chk_Max( res, a[i][j] - j );
			}
			list.push_back( (Node) { res + 1, i } );
		}

		std::sort( list.begin(), list.end(), 
				[]( const Node &_a, const Node &_b ) { 
					if( _a.res == _b.res ) 
						return _a.pos < _b.pos;
					return _a.res < _b.res; 
		});
		
		int ans = list.front().res;
		int res = ans;
		for( int i = 0; i < n; i ++ ) {
			if( res > list[i].res ) 
				res += a[ list[i].pos ].size();
			else {
				int k = list[i].pos;
				int size = a[k].size();
				for( int j = 0; j < size; j ++ ) {
					if( res <= a[k][j] ) {
						int tmp = ( a[k][j] - res ) + 1;
						res += tmp;
						ans += tmp;
					}
					res ++;
				}
			}
		}

		printf( "%d\n", ans );

		for( int i = 1; i <= n; i ++ ) 
			a[i].clear();
	}
}
