/*
 * f.cpp
 * Copyright (C) 2021 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU AGPLv3+ license.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

typedef long long ll;
typedef unsigned long long ull;

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
T pow( T a, int p ) {
	T res = 1;
	while( p ) {
		if( p & 1 ) 
			res = res * a;
		a = a * a;
		p >>= 1;
	}
	return res;
}/*}}}*/

struct SegmentTree {
	struct Lazy {
		ModInt mul, add, set;
		bool has_set;

		void operator+= ( const Lazy &_b ) { 
			if( _b.has_set ) {
				init();
				has_set = true; set = _b.set;
			}
			if( has_set ) {
				set *= mul;
				set += add;
			}
			else {
				mul *= _b.mul;
				add *= _b.mul;
				add += _b.add;
			}
		}
	};
	struct Node {
		int left, rig;
		ModInt sum;
		Node *son[2];
		Lazy lazy;

		void operator+=( const Lazy &_b ) {
			if( _b.has_set ) {
				sum = _b.set * len( left, rig );
			}
			sum *= _b.mul;
			sum += _b.add * len( left, rig );
		}

		bool has_lazy() { return lazy.has_lazy(); }

		void push_down() {
			if( son[0] ) {
				*son[0] += lazy;
			}
			if( son[1] )
				*son[1] += lazy;
			lazy.init();
		}
		void push_up() {
			ModInt l = 0, r = 0;
			if( son[0] ) 
				l = son[0] -> sum;
			if( son[1] ) 
				r = son[1] -> sum;
			sum = l + r;
		}
	};

	void set( int from, int to, int val, Node *rt ) {
		if( from <= rt.left && to <= rt.rig ) {
			*rt += lazy;
			return ;
		}

		rt -> push_down();
		int mid = ( rt.left + rt.rig ) >> 1;
		if( from <= mid )
	}
	void set( int left, int rig, Lazy val ) {
		set( left, rig, val, rt );
	}
};

int main() {
	
}
