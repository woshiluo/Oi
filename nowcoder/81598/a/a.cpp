/*
 * a.cpp 2024-07-23
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

const int N = 5e5 + 1e4;

int lowbit( ci32 cur ) { return cur & ( -cur ); }
struct BIT {
	int n;
	int bit[N];

	void init( int _n ) {
		n = _n;
		memset( bit, 0, sizeof(int) * ( n + 5 ) );
	}

	void add( i32 cur, ci32 val ) {
		for( ; cur <= n; cur += lowbit(cur) ) 
			bit[cur] += val;
	}
	int sum( i32 cur ) {
		if( cur == 0 ) 
			return 0;
		i32 res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += bit[cur];
		return res;
	}

	int ask( i32 cur ) {
		return sum(cur);
	}
};

BIT bit;

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 l = read<i32>();
	ci32 r = read<i32>();

	std::vector<i32> list;
	list.push_back(0);
	for( int i = 1; i <= n; i ++ ) {
		list.push_back( read<i32>() - 1 );
	}

	if( n <= r ) {
		printf( "Yes\n" );
		return 0;
	}

	bit.init(n + 16);
	std::sort( list.begin() + 1, list.end() );
	ci32 times = ( ( n - r ) / ( r - l ) ) + ( ( n - r ) % ( r - l ) != 0 );

	int p1 = 1, p2 = 1;
	for( int i = 0; i < times; i ++ ) {
		while( p1 < n && list[p1] + bit.ask(p1) <= 1 ) 
			p1 ++;
		while( p2 < n && p2 - p1 + 1 < l ) 
			p2 ++;
		if( p1 <= n && p2 <= n && list[p1] + bit.ask(p1) > 1 && p2 - p1 + 1 == l ) {
			bit.add( 1, -2 );
			bit.add( p2 + 1, 2 );
		}
		else {
			printf( "No\n" );
			return 0;
		}
	}

	printf( "Yes\n" );
	return 0;
}
