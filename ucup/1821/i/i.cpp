/*
 * i.cpp 2024-11-06
 * Copyright (C) 2024 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <charconv>
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
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ( ch - '0' );
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

// int gcd( ci32 a, ci32 b ) { return b? gcd( b, a % b ): a; }
// 
// struct SegmentTree {
// 	struct Data {
// 		bool has;
// 		int val;
// 
// 		Data operator+ ( const Data &_b ) {
// 			if( has && !_b.has )
// 				return *this;
// 			if( !has && _b.has ) 
// 				return _b;
// 			Data res;
// 			res.has = true;
// 			res.val = gcd( val, _b.val );
// 			return res;
// 		}
// 	};
// 
// 	struct Node {
// 		ci32 left, rig, mid;
// 		Data data;
// 		Node *son[2];
// 		Node( ci32 _left, ci32 _rig ): left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) {
// 			data.has = false;
// 			data.val = 0;
// 			son[0] = son[1] = 0;
// 		}
// 
// 		Node* get_son( ci32 k ) {
// 			if( son[k] ) 
// 				return son[k];
// 			if( k == 0 ) 
// 				son[k] = new Node( left, mid );
// 			else 
// 				son[k] = new Node( mid + 1, rig );
// 		}
// 	};
// };

int main() {
#ifdef woshiluo
	freopen( "i.in", "r", stdin );
	freopen( "i.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 q = read<i32>();
		std::vector<i32> a( n + 1 ), valid( n + 1 ), count( n + 1 );
		std::vector<bool> status( n + 1, false );
		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<i32>();
		}
		count[0] = n;
		i32 valid_count = 0;
		const auto update_valid = [&]( ci32 cur, ci32 new_value ) {
			count[ valid[cur] ] --;
			valid[cur] = new_value;
			count[ valid[cur] ] ++;
		};
		const auto update = [&]( ci32 cur, ci32 flag ) {
			if( status[cur] == flag ) 
				return ;
			status[cur] = flag;
			int k = flag? 1: -1;
			valid_count += k;
			for( int i = 1; 1LL * i * i <= cur; i ++ ) {
				if( cur % i == 0 ) {
					update_valid( i, valid[i] + k );
					if( cur / i != i ) 
						update_valid( cur / i, valid[ cur / i ] + k );
				}
			}
		};
		for( int i = 1; i < n; i ++ ) {
			update( i, a[i] > a[ i + 1 ] );
		}
		printf( "%d\n", count[valid_count] );
		for( int _ = 1; _ <= q; _ ++ ) {
			ci32 x = read<i32>();
			ci32 v = read<i32>();
			a[x] = v;
			if( x > 1 ) 
				update( x - 1, a[ x - 1 ] > a[x] );
			if( x != n ) 
				update( x, a[x] > a[ x + 1 ] );
			printf( "%d\n", count[valid_count] );
		}
	}
	
	return 0;
}
