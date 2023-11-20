/*
 * c.cpp 2023-10-22
 * Copyright (C) 2023 Woshiluo Luo <woshiluo.luo@outlook.com>
 *
 * 「Two roads diverged in a wood,and I—
 * I took the one less traveled by,
 * And that has made all the difference.」
 *
 * Distributed under terms of the GNU GNU AGPLv3+ license.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <vector>
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

const int N = 5e5 + 1e4;
const ll LLF = 0x3f3f3f3f3f3f3f3f;

struct SegmentTree {
	struct Node {
		int sum;
		bool lazy;
	};
	int n;
	Node tree[N << 2];

	void push_up( cint cur ) {
		tree[cur].sum = tree[ cur << 1 ].sum + tree[ cur << 1 | 1 ].sum;
	}
	void push_down( cint cur ) {
		if( tree[cur].lazy ) {
			tree[ cur << 1 ].sum = 0;
			tree[ cur << 1 ].lazy = 1;
			tree[ cur << 1 | 1 ].sum = 0;
			tree[ cur << 1 | 1 ].lazy = 1;
		}
	}

	void build( cint cur, cint left, cint rig ) {
		tree[cur].lazy = 0;
		if( left == rig ) {
			tree[cur].sum = 1;
			return ;
		}
		cint mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		
		push_up(cur);
	}
	void init( cint _n ) { n = _n; build( 1, 0, n ); }

	void set_0( cint from, cint to, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			tree[cur].sum = 0;
			tree[cur].lazy = 1;
			return ;
		}

		push_down(cur);
		cint mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			set_0( from, to, cur << 1, left, mid );
		if( to > mid ) 
			set_0( from, to, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	void set_0( cint left, cint rig ) { return set_0( left, rig, 1, 0, n ); }

	int sum( cint from, cint to, cint cur, cint left, cint rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur].sum;
		}

		push_down(cur);
		int res = 0;
		cint mid = ( left + rig ) >> 1;
		if( from <= mid ) 
			res += sum( from, to, cur << 1, left, mid );
		if( to > mid ) 
			res += sum( from, to, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
		return res;
	}
	int sum( cint left, cint rig ) { return sum( left, rig, 1, 0, n ); }
} sgt;

int main() {
#ifdef woshiluo
	freopen( "c.in", "r", stdin );
	freopen( "c.out", "w", stdout );
#endif
	int T = read<int>();
	while( T -- ) {
		struct Op { int l, r, x; };
		struct Diff { 
			int time; ll val; 
			bool operator< ( const Diff &_b ) const {
				return val < _b.val;
			}
		};

		int n = read<int>();

		std::vector<int> a( n + 1 );
		std::vector<Op> ops;
		std::vector<std::vector<Diff>> diff( n + 2 );
		diff[0].push_back((Diff){ 0, 0 } );
		ops.push_back( (Op) { 0, 0, 0} );

		for( int i = 1; i <= n; i ++ ) {
			a[i] = read<int>();
			diff[i].push_back((Diff) { 0, a[i] } );
		}
		int q = read<int>();
		sgt.init(q);
		for( int o = 1; o <= q; o ++ ) {
			cint l = read<int>();
			cint r = read<int>() + 1;
			cint x = read<int>();
			ops.push_back( (Op) { l, r, x } );
			diff[l].push_back((Diff) { o, x } );
			diff[r].push_back((Diff) { o, -x } );
		}
		for( auto &list: diff ) {
			cint size = list.size();
			for( int i = 1; i < size; i ++ ) {
				list[i].val += list[ i - 1 ].val;
			}
		}

		diff.resize( n + 1 );
		for( auto &list: diff ) {
			auto find = [](std::vector<Diff> &p) {
				ll min = LLF;
				cint size = p.size();
				for( int i = 0; i < size - 1; i ++ ) {
					if( sgt.sum( p[i].time, p[ i + 1 ].time - 1) ) 
						chk_Min( min, p[i].val );
				}
				assert( min != LLF );
				return min;
			};

			std::vector<Diff> p = list;
			// std::sort( p.begin(), p.end() );
			p.push_back( (Diff) { q + 1, 0 } );
			const ll min = find(p);
			cint size = p.size();
			for( int i = 0; i < size - 1; i ++ ) {
				if( p[i].val == min ) 
					continue;
				sgt.set_0( p[i].time, p[ i + 1 ].time - 1 );
			}
		}


		for( int i = 0; i <= q; i ++ ) {
			if( sgt.sum( i, i ) ) {
				std::vector<ll> sum( n + 2 );
				for( int j = 1; j <= i; j ++ ) {
					auto &[ l, r, x ] = ops[j]; 
					sum[l] += x;
					sum[r] -= x;
				}
				for( int j = 1; j <= n; j ++ ) {
					sum[j] += sum[j - 1];
				}
				for( int j = 1; j <= n; j ++ ) {
					sum[j] += a[j];
				}

				for( int j = 1; j <= n; j ++) { 
					printf( "%lld ", sum[j] );
				}
				printf( "\n" );
				break;
			}
		}

	}
}
