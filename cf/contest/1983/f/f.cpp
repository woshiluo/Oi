/*
 * f.cpp 2024-07-10
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

const int K = 30;

struct Trie {
	struct Node {
		int max;
		Node *son[2];
		Node() {
			max = -1;
			son[0] = son[1] = 0;
		}
		~Node() {
			if( son[0] ) 
				delete son[0];
			if( son[1] ) 
				delete son[1];
		}
		void insert( ci32 cur, ci32 k, ci32 val ) {
			chk_Max( max, val );
			if( k == -1 ) 
				return ;
			ci32 p = ( cur >> k ) & 1;
			if( !son[p] ) 
				son[p] = new Node();
			son[p] -> insert( cur, k - 1, val );
		}

		int query( ci32 cur, ci32 k, ci32 val ) {
			i32 res = -1;
			if( k == -1 ) 
				return max;
			ci32 p1 = ( cur >> k ) & 1;
			ci32 p2 = ( val >> k ) & 1;
			if( p2 ) {
				if( son[ p1 ^ 1 ] ) 
					chk_Max( res, son[ p1 ^ 1 ] -> query( cur, k - 1, val ) );
			}
			else {
				if( son[p1] ) 
					chk_Max( res, son[p1] -> query( cur, k - 1, val ) );
				if( son[p1 ^ 1] ) 
					chk_Max( res, son[p1 ^ 1] -> max );
			}
			return res;
		}
	};

	Node *rt;
	Trie() { rt = new Node(); }
	~Trie() { delete rt; }

	void insert( ci32 pos, ci32 max ) { rt -> insert( pos, K, max ); }

	int query( ci32 val, ci32 max ) { return rt -> query( val, K, max ); }
};

int main() {
#ifdef woshiluo
	freopen( "f.in", "r", stdin );
	freopen( "f.out", "w", stdout );
#endif

	i32 T = read<i32>();
	while( T -- ) {
		ci32 n = read<i32>();
		ci32 k = read<i32>();

		std::vector<i32> a(n);
		for( auto &x: a ) 
			x = read<i32>();

		i32 left = 0, rig = 1 << 30, res = 0;

		auto check = [&]( const i32 mid ) -> bool {
			Trie t;
			i64 count = 0;
			for( int i = 0; i < n; i ++ ) {
				ci32 ml = t.query( a[i], mid );
				t.insert( a[i], i );
				count += n - ( i - ml + 1 );
			}
			return count >= k;
		};
		while( left <= rig ) {
			ci32 mid = ( left + rig ) >> 1;
			if( check(mid) ) {
				res = mid;
				rig = mid - 1;
			}
			else 
				left = mid + 1;
		}
		printf( "%d\n", res );
	}
}
