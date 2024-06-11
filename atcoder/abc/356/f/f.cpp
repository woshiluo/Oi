/*
 * f.cpp 2024-06-01
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

const int N = 1e6 + 1e5;

i32 lowbit( ci32 cur ) { return cur & ( - cur ); }
struct BIT {
	int n;
	i64 tree[N];

	void init( int _n ) {
		n = _n;;
		memset( tree, 0, sizeof(i64) * ( n + 1 ) );
	}

	void add( i32 cur, i32 val ) {
		for( ; cur <= n; cur += lowbit(cur) )
			tree[cur] += val;
	}

	i64 query( i32 cur ) {
		if( cur == 0 ) 
			return 0;
		i64 res = 0;
		for( ; cur; cur -= lowbit(cur) ) 
			res += tree[cur];
		return res;
	}
} bit;

struct Query {
	int op;
	i64 x;
};

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	ci32 q = read<i32>();
	ci64 k = read<i64>();

	std::vector<Query> queries(q);
	std::vector<i64> nums;
	for( auto &query: queries ) {
		query.op = read<i32>();
		query.x = read<i64>();
		if( query.op == 2 ) {
			nums.push_back( query.x + k );
			nums.push_back( query.x - k - 1 );
		}
	}

	std::set<i64> set;
	std::sort( nums.begin(), nums.end() );
	nums.erase( std::unique( nums.begin(), nums.end() ), nums.end() );
	bit.init( nums.size() + 5 );

	auto find = [&]( ci64 cur ) {
		return std::lower_bound( nums.begin(), nums.end(), cur ) - nums.begin() + 1;
	};
	for( auto &query: queries ) {
		auto [op, x] = query;

		if( op == 1 ) {
			if( set.count(x) ) {
				set.erase(x);
				ci64 pos = find(x);
				bit.add( pos, -1 );
			}
			else {
				set.insert(x);
				ci64 pos = find(x);
				bit.add( pos, 1 );
			}
		}
		else {
			ci64 left = find( x - k - 1 );
			ci64 right = find( x + k );
			printf( "%lld\n", bit.query(right) - bit.query(left) );
		}
	}

	return 0;
}
