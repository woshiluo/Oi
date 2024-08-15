/*
 * f.cpp 2024-08-15
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

#include <set>
#include <map>
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

using i128 = __int128;
using u128 = unsigned __int128;
using ci128 = const i128;
using cu128 = const u128;

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

constexpr i64 gcd( i64 a, i64 b ) { return b? gcd( b, a % b ): a; }

// x / y
struct Frac {
	i64 x, y;
	constexpr Frac(): x{0}, y{1} {}
	constexpr Frac(i32 cur): x{cur}, y{1} {}
	constexpr Frac(i32 _x, i32 _y): x{_x}, y{_y} {}
	// x1 / y1 < x2 / y2 => x1 * y2 < x2 * y1
	constexpr void update() {
		ci64 p = gcd( x, y );
		x /= p;
		y /= p;
	}
	constexpr bool operator< ( const Frac &_b ) const {
		return ( (__int128)x * _b.y ) < ( (__int128)_b.x * y );
	}

	constexpr Frac& operator*= ( const Frac &_b ) {
		x *= _b.x;
		y *= _b.y;
		this -> update();
		return *this;
	}
	constexpr Frac& operator-= ( const Frac &_b ) {
		x = (i128)x * _b.y - (i128)_b.x * y;
		y *= _b.y;
		this -> update();
		return *this;
	}
};

const int N = 1024;

bool vis[N][N];

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	std::vector<std::pair<i32, i32>> list;
	std::map<Frac, std::set<Frac>> mp;
	std::set<Frac> par_x, par_y;

	ci32 n2 = n * n; 

	for( int i = 1; i <= n2; i ++ ) {
		ci32 x = read<i32>();
		ci32 y = read<i32>();

		if( vis[x][y] ) 
			printf( "0" );
		else {
			printf( "1" );
			for( auto &[ px, py ]: list ) {
				if( px == x ) {
					for( int j = 1; j <= n; j ++ ) 
						vis[x][j] = true;
				}
				else if( py == y ) {
					for( int j = 1; j <= n; j ++ ) 
						vis[j][y] = true;
				}
				if( px == x || py == y ) 
					continue;

				Frac k = (Frac){ py - y, px - x };
				k.update();
				ci32 dx = k.y;
				ci32 dy = k.x;

				{
					i32 cx = x, cy = y;
					while( cx >= 1 && cy >= 1 && cx <= n && cy <= n ) {
						vis[cx][cy] = true;
						cx += dx; 
						cy += dy;
					}
				}
				{
					i32 cx = x, cy = y;
					while( cx >= 1 && cy >= 1 && cx <= n && cy <= n ) {
						vis[cx][cy] = true;
						cx -= dx; 
						cy -= dy;
					}
				}
			}
			list.emplace_back( x, y );
		}
	}
}
