/*
 * 10.cpp 2024-08-12
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

int cur_time = 0;
std::vector<bool> set[K];
std::vector<i32> pre[K];
i32 la_force[K];

i32 full_pow( ci32 cur ) { return 1 << cur; }
i32 get_pos( ci32 cur, ci32 pos ) { return ( cur >> pos ) & 1; }
struct Trie {
	struct Node {
		i32 la, depth;
		Node *son[2];

		Node( ci32 _dep, ci32 cur ) {
			la = cur;
			depth = _dep;
			son[0] = son[1] = 0;
		}
		void update() {
			if( depth == 0 )
				return ;
			ci32 force_time = la_force[ depth - 1 ];
			if( force_time > la ) {
				ci32 k = set[ depth - 1 ][force_time];

				son[k] = merge( son[k], son[ k ^ 1 ] );
				son[k ^ 1] = 0;

				la = force_time;
			}

			ci32 rev_count = pre[ depth - 1 ][cur_time] - pre[ depth - 1 ][la];
			if( rev_count & 1 ) 
				std::swap( son[0], son[1] );

			la = cur_time;
		}

		void insert( ci32 cur ) {
			this -> update();
			if( depth == 0 ) 
				return ;
			ci32 k = get_pos( cur, depth - 1 ); 
			if( son[k] == 0 ) 
				son[k] = new Node( depth - 1, cur_time );
			son[k] -> insert(cur);
		}

		i32 query( ci32 cur ) {
			this -> update();
			if( depth == 0 ) 
				return 0;
			ci32 k = get_pos( cur, depth - 1 );
			if( son[ k ^ 1 ] ) 
				return full_pow(depth - 1) | son[ k ^ 1 ] -> query(cur);
			else if( son[k] )
				return son[k] -> query(cur);
			else
				return 0;
		}
	};

	static Node* merge( Node *lp, Node *rp ) {
		if( lp == 0 ) 
			return rp;
		if( rp == 0 ) 
			return lp;
		if( lp == 0 && rp == 0 ) 
			return 0;

		lp -> update();
		rp -> update();

		lp -> son[0] = merge( lp -> son[0], rp -> son[0] );
		lp -> son[1] = merge( lp -> son[1], rp -> son[1] );

		delete rp;
		return lp;
	}

	Node *rt;

	Trie() {
		rt = new Node( K - 1, 0 );
	}

	void insert( ci32 cur ) { return rt -> insert(cur); }
	i32 query( ci32 cur ) { return rt -> query(cur); }

};

int main() {
#ifdef woshiluo
	freopen( "10.in", "r", stdin );
	freopen( "10.out", "w", stdout );
#endif

	

	i32 T = read<i32>();
	while( T --  ) {
		ci32 n = read<i32>();
		ci32 m = read<i32>();

		Trie trie;

		cur_time = 0;
		for( int k = 0; k < K; k ++ ) {
			set[k].resize(0);
			pre[k].resize(0);
			set[k].resize(m + 1, 0);
			pre[k].resize(m + 1, 0);
			la_force[k] = 0;
		}

		for( int i = 1; i <= n; i ++ ) {
			trie.insert( read<i32>() );
		}

		for( int i = 1; i <= m; i ++ ) {
			cur_time = i;
			ci32 opt = read<i32>();
			ci32 a = read<i32>();
			for( int k = 0; k < K; k ++ ) 
				pre[k][i] += pre[k][ i - 1 ];
			if( opt == 1 ) {
				trie.insert(a);
			}
			else if( opt == 5 ) {
				printf( "%d\n", trie.query(a) );
			}
			else {
				for( int k = 0; k < K; k ++ ) {
					if( opt == 2 ) {
						if( get_pos( a, k ) ) {
							la_force[k] = i;
							set[k][i] = 1;
						}
					}
					if( opt == 3 ) {
						if( !get_pos( a, k ) ) {
							la_force[k] = i;
							set[k][i] = 0;
						}
					}
					if( opt == 4 ) {
						if( get_pos( a, k ) ) {
							pre[k][i] ++;
						}
					}
				}
			}
		}
	}
}
