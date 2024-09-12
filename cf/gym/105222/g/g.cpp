/*
 * g.cpp 2024-09-11
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

const int K = 32;

int chk_pos( int cur, int pos ) { return ( cur >> pos ) & 1; }

struct Trie {
	struct Node {
		int pos, dep;
		Node *nxt[2];
		Node( ci32 _dep ) {
			dep = _dep;
			pos = 0;
			nxt[0] = nxt[1] = 0;
		}
		void insert( ci32 val, ci32 np ) {
			if( dep == 0 ) {
				this -> pos = np;
				return ;
			}
			int k = chk_pos( val, dep - 1 );
			if( !this -> nxt[k] ) 
				this -> nxt[k] = new Node( dep - 1 );
			this -> nxt[k] -> insert( val, np );
		}

		 int max_pos( ci32 val ) {
			 if( dep == 0 ) {
				 return this -> pos;
			 }
			 ci32 k = chk_pos( val, dep - 1 );
			 if( this -> nxt[ k ^ 1 ] )
				 return this -> nxt[ k ^ 1 ] -> max_pos(val);
			 else 
				 return this -> nxt[k] -> max_pos(val);
		 }
		 int min_pos( ci32 val ) {
			 if( dep == 0 ) {
				 return this -> pos;
			 }
			 ci32 k = chk_pos( val, dep - 1 );
			 if( this -> nxt[k] )
				 return this -> nxt[k] -> min_pos(val);
			 else 
				 return this -> nxt[ k ^ 1 ] -> min_pos(val);
		 }
	};

	Node *rt;
	Trie() { rt = new Node(K); }

	void insert( ci32 val, ci32 pos ) { rt -> insert( val, pos ); }
	int min_pos( ci32 val ) { return rt -> min_pos( val ); }
	int max_pos( ci32 val ) { return rt -> max_pos( val ); }
} trie;

int main() {
#ifdef woshiluo
	freopen( "g.in", "r", stdin );
	freopen( "g.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 q = read<i32>();
	std::vector<i32> x( n + 1 );
	for( int i = 1; i <= n; i ++ ) {
		x[i] = read<i32>();
		trie.insert( x[i], i );
	}
	for( int _ = 1; _ <= q; _ ++ ) {
		ci64 a = read<i64>();
		ci64 b = read<i64>();

		const auto f = [&] ( ci64 cx ) { return ( a ^ cx ) - b; };
		const auto check = [&] ( ci32 p1, ci32 p2 ) { return 1LL * f( x[p1] ) * f( x[p2] ) <= 0; };

		ci32 p1 = trie.min_pos(a);
		ci32 p2 = trie.max_pos(a);

		if( p1 == p2 ) {
			if( f( x[p1] ) == 0 ) 
				printf( "1\n" );
			else 
				printf( "-1\n" );
			continue;
		}

		if( !check( p1, p2 ) ) {
			printf( "-1\n" );
			continue;
		}

		i32 l = Min( p1, p2 );
		i32 r = Max( p1, p2 );
		while( 1 ) {
			ci32 mid = ( l + r ) >> 1;
			if( check( mid, r ) ) {
				if( mid == r - 1 ) {
					printf( "%d\n", mid );
					break;
				}
				l = mid;
			}
			else {
				if( l == mid - 1 ) {
					printf( "%d\n", l );
					break;
				}
				r = mid;
			}
		}
	}

	return 0;
}
