/*
 * l.cpp 2024-09-04
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

enum Status {
	status_hit,
	status_miss,
	status_sunk,
	status_already,
};

// So we make hited as miss, I hope it work
const int N = 128;
bool vis[N][N];
Status query( ci32 x, ci32 y ) {
	if( vis[x][y] )
		return status_already;
	vis[x][y] = true;
	printf( "%d %d\n", x, y  );
	fflush(stdout);

	static char buf[16];
	scanf( "%s", buf );
	if( buf[0] == 'm' )
		return status_miss;
	else if( buf[0] == 's' )
		return status_sunk;
	else 
		return status_hit;
}

void try_query( ci32 x, ci32 y, ci32 dx, ci32 dy, ci32 n ) {
	if( x <= 0 || y <= 0 || x > n || y > n ) 
		return ;
	const auto status = query( x, y );
	if( status != status_miss )
		try_query( x + dx, y + dy, dx, dy, n );
}

const i32 dx[4] = { 0, 0, +1, -1 };
const i32 dy[4] = { +1, -1, 0, 0 };


int main() {
#ifdef woshiluo
//	freopen( "l.in", "r", stdin );
//	freopen( "l.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 k = read<i32>();

	std::vector<std::pair<i32, i32>> hited;
	for( int i = 1; i <= n; i += 5 ) {
		{
			i32 x = 1, y = i;
			while( x <= n && y <= n ) {
				if( query( x, y ) == status_hit )
					hited.emplace_back( x, y );
				x ++, y ++;
			}
		}
		if( i == 1 ) 
			continue;
		{
			i32 x = i, y = 1;
			while( x <= n && y <= n ) {
				if( query( x, y ) == status_hit )
					hited.emplace_back( x, y );
				x ++, y ++;
			}
		}
	}

	for( auto &[ x, y ]: hited ) {
		for( int p = 0; p < 4; p ++ ) {
			try_query( x + dx[p], y + dy[p], dx[p], dy[p], n );
		}
	}

	return 0;
}
