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

#include <stack>
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

const int N = 1100;

int a[N];

struct Node {
	bool pair;
	int cnt;
};

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n = read<int>();
	ll ans = 0;
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	std::stack<Node> st;
	for( int i = 1; i <= n; i ++ ) {
		if( i & 1 ) {
			st.push( (Node) { false, a[i] } );
		}
		else {
			int tmp = a[i]; bool paired = false;
			while( tmp && !st.empty() ) {
				Node top = st.top(); st.pop();
				if( top.pair ) {
					if( paired ) {
						ans += top.cnt;
						top.cnt ++;
						st.push(top);
						paired = false;
					}
					continue;
				}
				int d = Min( tmp, top.cnt );
				paired = true;
				top.cnt -= d; tmp -= d;
				ans += d;
				if( top.cnt ) 
					st.push(top);
			}
			if( !st.empty() && st.top().pair ) {
				Node top = st.top(); st.pop();
				if( top.pair ) {
					if( paired ) {
						ans += top.cnt;
						top.cnt ++;
						st.push(top);
					}
					continue;
				}
			}
			if( tmp != 0 ) {
				while( !st.empty() ) 
					st.pop();
			}
			else 
				st.push( (Node) { true, 1 } );
		}
	}
	printf( "%lld\n", ans );
}
