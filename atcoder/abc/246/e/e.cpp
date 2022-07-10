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

#include <queue>
#include <algorithm>

using std::make_pair;

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

const int N = 2100;

bool mp[N][N];
int step[N][N];
int dx[] = { +1, +1, -1, -1 };
int dy[] = { +1, -1, +1, -1 };

int main() {
	int n = read<int>();
	int sx = read<int>(); int sy = read<int>();
	int ex = read<int>(); int ey = read<int>();
	for( int i = 1; i <= n; i ++ ) {
		static char str[N];
		scanf( "%s", str + 1 );
		for( int j = 1; j <= n; j ++ ) 
			mp[i][j] = ( str[j] == '#' );
	}

	memset( step, -1, sizeof(step) );
	std::queue< std::pair<int, int> > q;
	q.push( make_pair( sx, sy ) ); step[sx][sy] = 0;
	auto check = [&]( const auto node, const int g ) {
		if( node.first >= 1 && node.second >= 1 && node.first <= n && node.second <= n
				&& ( step[ node.first ][ node.second ] == -1 || step[ node.first ][ node.second ] > g )
				&& mp[ node.first ][ node.second ] == false ) {
			return true;
		}
		return false;
	};
	while( !q.empty() ) {
		auto cur = q.front(); q.pop();
		bool block[4];
		memset( block, false, sizeof(block) );
		int cnt = 0;
		for( int d = 1; d <= n; d ++ ) {
			if( cnt == 4 ) 
				break;
			for( int i = 0; i < 4; i ++ ) {
				if( block[i] ) 
					continue;
				auto tmp = cur;
				tmp.first += dx[i] * d;
				tmp.second += dy[i] * d;
				if( check( tmp, step[cur.first][cur.second] ) ) {
					step[tmp.first][tmp.second] = step[cur.first][cur.second] + 1;
					q.push(tmp);
				}
				else {
					block[i] = true;
					cnt ++;
				}
			}
		}
	}
	printf( "%d\n", step[ex][ey] );
}
