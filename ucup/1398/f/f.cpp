/*
 * f.cpp 2024-10-09
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
#include <cinttypes>

#include <map>
#include <tuple>
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

const i32 INF = 0x3f3f3f3f;

struct SegmentTree {// {{{
	struct Node {
		ci32 left, rig, mid;
		i32 max;
		Node* son[2];

		Node( ci32 _l, ci32 _r ): left(_l), rig(_r), mid( ( _l + _r ) >> 1 ) {
			max = -INF;
			son[0] = son[1] = 0;
		}

		Node* get_son( ci32 k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[k] = new Node( left, mid );
			else 
				son[k] = new Node( mid + 1, rig );
			return son[k];
		}

		void push_up() { this -> max = Max( get_son(0) -> max, get_son(1) -> max ); }

		std::pair<i32, i32> search_right( ci32 from, ci32 target ) {
			if( left == rig ) {
				return std::make_pair( rig, this -> max );
			}
			if( mid < from ) 
				return get_son(1) -> search_right( from, target );
			if( this -> max < target ) {
				return std::make_pair( rig, this -> max );
			}
			else {
				const auto p1 = get_son(0) -> search_right( from, target );
				if( p1.second >= target ) 
					return p1;
				else 
					return get_son(1) -> search_right( from, target );
			}
		}
		std::pair<i32, i32> search_right_strict( ci32 from, ci32 target ) {
			if( left == rig ) {
				return std::make_pair( rig, this -> max );
			}
			if( mid < from ) 
				return get_son(1) -> search_right_strict( from, target );
			if( this -> max <= target ) {
				return std::make_pair( rig, this -> max );
			}
			else {
				const auto p1 = get_son(0) -> search_right_strict( from, target );
				if( p1.second > target ) 
					return p1;
				else 
					return get_son(1) -> search_right_strict( from, target );
			}
		}
		std::pair<i32, i32> search_left( ci32 from, ci32 target ) {
			if( left == rig ) {
				return std::make_pair( left, this -> max );
			}
			if( from <= mid ) 
				return get_son(0) -> search_left( from, target );
			if( this -> max < target ) {
				return std::make_pair( left, this -> max );
			}
			else {
				const auto p1 = get_son(1) -> search_left( from, target );
				if( p1.second >= target ) 
					return p1;
				else 
					return get_son(0) -> search_left( from, target );
			}
		}
		std::pair<i32, i32> search_left_strict( ci32 from, ci32 target ) {
			if( left == rig ) {
				return std::make_pair( left, this -> max );
			}
			if( from <= mid ) 
				return get_son(0) -> search_left_strict( from, target );
			if( this -> max <= target ) {
				return std::make_pair( left, this -> max );
			}
			else {
				const auto p1 = get_son(1) -> search_left_strict( from, target );
				if( p1.second > target ) 
					return p1;
				else 
					return get_son(0) -> search_left_strict( from, target );
			}
		}
		void update( ci32 pos, ci32 val ) {
			if( left == rig ) {
				this -> max = val;
				return ;
			}
			if( pos <= mid ) 
				get_son(0) -> update( pos, val );
			else 
				get_son(1) -> update( pos, val );

			this -> push_up();
		}
	};
	Node *rt;
	SegmentTree( ci32 n ) { rt = new Node( 1, n ); }
	void update( ci32 pos, ci32 val ) { rt -> update( pos, val ); }
	std::pair<i32, i32> search_left( ci32 from, ci32 target ) { return rt -> search_left( from, target ); }
	std::pair<i32, i32> search_right( ci32 from, ci32 target ) { return rt -> search_right( from, target ); }
	std::pair<i32, i32> search_right_strict( ci32 from, ci32 target ) { return rt -> search_right_strict( from, target ); }
};// }}}

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif
	ci32 n = read<i32>();
	ci32 q = read<i32>();

	std::vector<i32> a( n + 1 ), rev_a( n + 1 );
	std::vector<std::tuple<i32, bool,i32>> qs;
	// 1 add
	// 0 sub
	
	for( int i = 1; i <= n; i ++ ) 
		a[i] = read<i32>();

	std::vector<i32> b = a;

	for( int i = 1; i <= q; i ++ ) {
		static char buf[8];
		i32 x;
		scanf( "%s%d", buf, &x );
		qs.emplace_back( i, buf[0] == '+', x );
	}

	std::vector<i64> ans( q + 1 );

	{
		i64 res = 0;
		SegmentTree t1(n);
		for( int i = 1; i <= n; i ++ ) {
			t1.update( i, a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			auto [ p1, x1 ] = t1.search_left( i - 1, a[i] );
			auto [ p2, x2 ] = t1.search_right_strict( i + 1, a[i] );
			p1 += ( x1 >= a[i] );
			chk_Min( p1, i );
			p2 -= ( x2 > a[i] );
			chk_Max( p2, i );
			res += 1LL * ( i - p1 + 1 ) * ( p2 - i + 1 ) * a[i];
		}
		for( const auto &[id, op, x]: qs ) {
			if( op == 1 ) {
				ci32 cur = a[x] + 1;
				a[x] = cur;
				auto [ p1, x1 ] = t1.search_left( x - 1, cur );
				auto [ p2, x2 ] = t1.search_right( x + 1, cur );
				p1 += ( x1 >= cur );
				chk_Min( p1, x );
				p2 -= ( x2 >= cur );
				chk_Max( p2, x );
				res += 1LL * ( x - p1 + 1 ) * ( p2 - x + 1 );
				t1.update( x, cur );
			}
			else {
				ci32 cur = a[x] - 1;
				a[x] = cur;
				auto [ p1, x1 ] = t1.search_left( x - 1, cur + 1 );
				auto [ p2, x2 ] = t1.search_right( x + 1, cur + 1 );
				p1 += ( x1 >= cur + 1 );
				chk_Min( p1, x );
				p2 -= ( x2 >= cur + 1 );
				chk_Max( p2, x );
				res -= 1LL * ( x - p1 + 1 ) * ( p2 - x + 1 );
				t1.update( x, cur );
			}
			ans[id] += res;
		}
	}

	for( int i = 1; i <= n; i ++ ) 
		a[i] = b[i] * -1;

	{
		i64 res = 0;
		SegmentTree t1(n);
		for( int i = 1; i <= n; i ++ ) {
			t1.update( i, a[i] );
		}
		for( int i = 1; i <= n; i ++ ) {
			auto [ p1, x1 ] = t1.search_left( i - 1, a[i] );
			auto [ p2, x2 ] = t1.search_right_strict( i + 1, a[i] );
			p1 += ( x1 >= a[i] );
			chk_Min( p1, i );
			p2 -= ( x2 > a[i] );
			chk_Max( p2, i );
			res += 1LL * ( i - p1 + 1 ) * ( p2 - i + 1 ) * a[i];
		}
		for( const auto &[id, op, x]: qs ) {
			if( op == 0 ) {
				ci32 cur = a[x] + 1;
				a[x] = cur;
				auto [ p1, x1 ] = t1.search_left( x - 1, cur );
				auto [ p2, x2 ] = t1.search_right( x + 1, cur );
				p1 += ( x1 >= cur );
				chk_Min( p1, x );
				p2 -= ( x2 >= cur );
				chk_Max( p2, x );
				res += 1LL * ( x - p1 + 1 ) * ( p2 - x + 1 );
				t1.update( x, cur );
			}
			else {
				ci32 cur = a[x] - 1;
				a[x] = cur;
				auto [ p1, x1 ] = t1.search_left( x - 1, cur + 1 );
				auto [ p2, x2 ] = t1.search_right( x + 1, cur + 1 );
				p1 += ( x1 >= cur + 1 );
				chk_Min( p1, x );
				p2 -= ( x2 >= cur + 1 );
				chk_Max( p2, x );
				res -= 1LL * ( x - p1 + 1 ) * ( p2 - x + 1 );
				t1.update( x, cur );
			}
			ans[id] += res;
		}
	}

	for( int i = 1; i <= q; i ++ ) 
		printf( "%" PRId64 "\n", ans[i] );

	return 0;
}
