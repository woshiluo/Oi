/*
 * c.cpp
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

#include <queue>
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

struct Node { int x, y; };

int dx[] = { +1, +1, -1, -1 };
int dy[] = { +1, -1, +1, -1 };

int lcm( int a, int b ) { return a * b / std::__gcd( a, b ); }

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		cint n = read<int>(); 
		cint m = read<int>();
		cint mnm = Max( n, m );

		int res = 0;
		for( int r = 1; r <= mnm; r ++ ) {
			for( int s = r; s <= mnm; s ++ ) {
				std::vector<std::vector<bool>> vis( n, std::vector<bool>(m, false));
				std::queue<Node> q;
				q.push( (Node) { 0, 0 } ); vis[0][0] = true;
				auto check = [&]( const Node &cur ) { 
					if( cur.x < 0 || cur.y < 0 || cur.x >= n || cur.y >= m || vis[ cur.x ][ cur.y ] ) 
						return false;
					return true;
				};
				int cnt = 1;
				while( !q.empty() ) {
					Node cur = q.front(); q.pop();
					for( int i = 0; i < 4; i ++ ) {
						{
							Node nxt = cur;
							nxt.x += dx[i] * s; nxt.y += dy[i] * r;
							if( check(nxt) ) {
								cnt ++;
								vis[ nxt.x ][ nxt.y ] = true;
								q.push(nxt);
							}
						}
						{
							Node nxt = cur;
							nxt.x += dx[i] * r; nxt.y += dy[i] * s;
							if( check(nxt) ) {
								cnt ++;
								vis[ nxt.x ][ nxt.y ] = true;
								q.push(nxt);
							}
						}
					}
				}
				res += ( cnt == n * m );
			}
		}

		printf( "%d\n", res );
	}
}
