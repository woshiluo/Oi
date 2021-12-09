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

#include <queue>
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

const int N = 2e5 + 1e4;

ll s[N], t[N];
bool vis[N];
std::queue<int> q;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int n = read<ll>();
	for( int i = 1; i <= n; i ++ ) {
		s[i] = read<ll>();
	}
	for( int i = 1; i <= n; i ++ ) {
		t[i] = read<ll>();
	}

	for( int i = 1; i <= n; i ++ ) {
		q.push(i);
		vis[i] = true;
	}
	while( !q.empty() ) {
		int cur = q.front(); q.pop(); vis[cur] = false;
		int nxt = cur + 1;
		if( nxt > n ) 
			nxt -= n;
		if( t[cur] + s[cur] < t[nxt] ) {
			t[nxt] = t[cur] + s[cur];
			if( !vis[nxt] ) {
				vis[nxt] = true;
				q.push(nxt);
			}
		}
	}
	for( int i = 1; i <= n; i ++ )
		printf( "%lld\n", t[i] );
}
