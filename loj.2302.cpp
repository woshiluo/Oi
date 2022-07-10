/*
 * loj.2302.cpp
 * Copyright (C) 2022 Woshiluo Luo <woshiluo.luo@outlook.com>
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

typedef const int cint;
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


const int N = 1e6 + 1e5;

inline int full_pow( cint cur ) { return 1 << cur; }
bool chk_pos( cint cur, cint p ) { return cur & full_pow(p); }

struct SegmentTree {
	int n;
	int tree[ N << 2 ];

	void init( cint _n ) { n = _n; }

	void add( cint pos, cint val, cint cur, cint left, cint rig ) {
		if( left == rig ) {
			tree[cur] += full_pow(pos);
			return ;
		}

		cint mid = ( left + rig ) >> 1;
		cint lpart = ( mid - left + 1 );
		if( pos < lpart * 30 ) 
			add( pos, val, cur << 1, left, mid );
		else
			add( pos - lpart * 30, val, cur << 1 | 1, mid + 1, rig );
	}
	void add( cint pos, cint val ) { add( pos, val, 1, 1, n ); }

	int get( cint pos, cint cur, cint left, cint rig ) {
		if( left == rig ) 
			return chk_pos( tree[cur], pos );

		cint mid = ( left + rig ) >> 1;
		cint lpart = ( mid - left + 1 );
		if( pos < lpart * 30 ) 
			return get( pos, cur, left, mid );
		else
			return get( pos - lpart * 30, cur, mid + 1, rig );

		return 0;
	}
	int get( cint pos ) { return get( pos, 1, 1, n ); }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "loj.2302.in", "r", stdin );
	freopen( "loj.2302.out", "w", stdout );
#endif
	cint n = read<int>();
	int _ =read<int>(); _ = read<int>(); _ = read<int>();

	sgt.init( (int)(1e6) );
	for( int i = 1; i <= n; i ++ ) {
		int op = read<int>();
		if( op == 1 ) {
			int a, b;
			a = read<int>(); b = read<int>();
			int p = 0;
			while( a ) {
				if( a & 1 ) {
					sgt.add( p + b, 1 );
				}
				a >>= 1;
				p ++;
			}
		}
		else {
			printf( "%d\n", sgt.get( read<int>() ) );
		}
	}
}
