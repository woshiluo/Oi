/*
 * d.cpp
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


const int N = 9e5 + 1e4;
const int BLOCK = 550;
const int INF = 0x3f3f3f3f;

int n;
int dis[N], la[N], a[N], b[N];

void dfs( int cur ) {
	if( cur == n ) 
		return ;
	dfs( la[cur] );
	if( cur > n && cur <= 2 * n ) 
		printf( "%d ", cur - n );
}

int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif
	n = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		a[i] = read<int>();
	}
	for( int i = 1; i <= n; i ++ ) {
		b[i] = read<int>();
	}
	memset( dis, INF, sizeof(dis) );
	dis[n] = 0;
	std::deque<int> q;
	q.push_back(n);
	// 0 - n ori node
	// n + 1 - 2n wait drop
	// 2n + 1 - ... block 
	while( !q.empty() ) {
		int cur = q.front(); q.pop_front();
		if( cur <= n ) {
			// to block
			int from = cur - a[cur], to = cur;
			int lblock = from / BLOCK + 2;
			int rblock = to / BLOCK;
			for( int i = Max( 1, lblock ); i <= rblock; i ++ ) {
				if( dis[cur] < dis[ i + 2 * n ] ) {
					dis[ i + 2 * n ] = dis[cur];
					la[ i + 2 * n ] = cur;
					q.push_front( i + 2 * n );
				}
			}
			for( int i = from; i < Min( to + 1, lblock * BLOCK ); i ++ ) {
				int nxt = i + n;
				if( i == 0 ) 
					nxt = i;
				if( dis[cur] + 1 < dis[nxt] ) {
					dis[nxt] = dis[cur] + 1;
					la[nxt] = cur;
					q.push_back(nxt);
				}
			}
			for( int i = Max( from, rblock * BLOCK ); i <= to; i ++ ) {
				int nxt = i + n;
				if( i == 0 ) 
					nxt = i;
				if( dis[cur] + 1 < dis[nxt] ) {
					dis[nxt] = dis[cur] + 1;
					la[nxt] = cur;
					q.push_back(nxt);
				}
			}
		}
		else if( cur <= 2 * n ) {
			int k = cur - n;
			if( dis[cur] < dis[ k + b[k] ] ) {
				dis[ k + b[k] ] = dis[cur];
				la[ k + b[k] ] = cur;
				q.push_front( k + b[k] );
			}
		}
		else {
			int k = cur - 2 * n;
			for( int i = ( k - 1 ) * BLOCK; i < BLOCK * k; i ++ ) {
				int nxt = i + n;
				if( i == 0 ) 
					nxt = i;
				if( dis[cur] + 1 < dis[nxt] ) {
					dis[nxt] = dis[cur] + 1;
					la[nxt] = cur;
					q.push_back(nxt);
				}
			}
		}
	}
	if( dis[0] == INF ) {
		printf( "%d\n", -1 );
		return 0;
	}
	printf( "%d\n", dis[0] );
	dfs(0);
	printf( "%d", 0 );
}
