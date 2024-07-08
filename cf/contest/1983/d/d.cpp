/*
 * d.cpp 2024-07-07
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
T pow( T a, i32 p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

const int M = 2e5 + 1e4;

inline int lowbit( int cur ) { return cur & ( - cur ); }
struct BIT {
	int n;
	int bit[M];
	BIT() {
		n = M - 10;
		memset( bit, 0, sizeof(bit) );
	}
	void erase() {
		memset( bit, 0, sizeof(bit) );
	}
	void add( int cur, int val ) {
		for( ; cur < n; cur += lowbit(cur) ) 
			bit[cur] += val;
	}
	int sum( int cur ) {
		int res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += bit[cur];
		return res;
	}
};

BIT bit;


int main() {
#ifdef woshiluo
	freopen( "d.in", "r", stdin );
	freopen( "d.out", "w", stdout );
#endif

	
	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		std::vector<i32> a(n), b(n);
		std::map<i32, i32> ma, mb;
		i64 r1 = 0, r2 = 0;

		{
			for( auto &x: a ) {
				x = read<i32>();
				ma[x] ++;
				r1 += bit.sum(x);
				bit.add(x, 1);
			}
			bit.erase();
		}
		{
			for( auto &x: b ) {
				x = read<i32>();
				mb[x] ++;;
				r2 += bit.sum(x);
				bit.add(x, 1);
			}
			bit.erase();
		}

		if( ma != mb || std::abs( r2 - r1 ) & 1 ) 
			printf( "NO\n" );
		else
			printf( "YES\n" );
	}
}
