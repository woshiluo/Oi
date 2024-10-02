/*
 * l.cpp 2024-10-02
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <queue>
#include <utility>
#include <vector>
#include <algorithm>

using i32 = int32_t;
using u32 = uint32_t;
using ci32 = const int32_t;
using cu32 = const uint32_t;

using i64 = int64_t;
using u64 = uint64_t;
using ci64 = const int64_t;
using cu64 = const uint64_t;

inline bool isdigit( const char cur ) { return cur >= '0' && cur <= '9'; }/*{{{*/
template <class T> 
constexpr T Max( T a, T b ) { return a > b? a: b; }
template <class T> 
constexpr T Min( T a, T b ) { return a < b? a: b; }
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
constexpr T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int N = 1024;
const int K = 6;

int dis[N][N];
bool mp[N][N];

int dx1[] = { -1, -1, 0, 0, 1, 1 };
int dy1[] = { -1, 0, 1, -1, 0, -1 };

int dx2[] = { -1, -1, 0, 0, 1, 1 };
int dy2[] = { 0, 1, 1, -1, 1, 0 };

int main() {
#ifdef woshiluo
	freopen( "l.in", "r", stdin );
	freopen( "l.out", "w", stdout );
#endif

	memset( dis, 0x3f, sizeof(dis) );
	ci32 n = read<i32>();
	ci32 m = read<i32>();

	for( int i = 1; i <= n; i ++ ) {
		static char buf[N];
		scanf( "%s", buf + 1 );
		for( int j = 1; j <= m; j ++ )
			mp[i][j] = ( buf[j] == '#' );
	}

	std::deque<std::pair<i32, i32>> q;
	for( int i = 1; i <= m; i ++ ) {
		if( mp[1][i] ) {
			dis[1][i] = 0;
			q.push_front( std::make_pair( 1, i ) );
		}
		else {
			dis[1][i] = 1;
			q.push_back( std::make_pair( 1, i ) );
		}
	}

	while( !q.empty() ) {
		const auto [x, y] = q.front(); q.pop_front();
		bool x1 = ( x & 1 );
		for( int k = 0; k < K; k ++ ) {
			ci32 nx = x + ( x1? dx1: dx2 )[k];
			ci32 ny = y + ( x1? dy1: dy2 )[k];
			if( nx <= 0 || ny <= 0 || nx > n || ny > m ) 
				continue;
			if( mp[nx][ny] ) {
				if( dis[x][y] < dis[nx][ny] ) {
					dis[nx][ny] = dis[x][y];
					q.emplace_front( nx, ny );
				}
			}
			else {
				if( dis[x][y] + 1 < dis[nx][ny] ) {
					dis[nx][ny] = dis[x][y] + 1;
					q.emplace_back( nx, ny );
				}
			}
		}
	}

	i32 min = dis[n][1];
	for( int i = 1; i <= m; i ++ ) {
		chk_Min( min, dis[n][i] );
	}
	printf( "%d\n", min );
}
