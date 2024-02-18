/*
 * luogu.2523.cpp 2024-02-08
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

const double DINF = 1e18;

std::vector<double> list;

struct SegmentTree {
	struct Segment {
		const double k, b;
		double get_x( int x ) {
			return k * list[x] + b;
		}
		Segment( double _k, double _b ) :k(_k), b(_b) {}
	};
	struct Node {
		Segment *seg;
		i32 left, rig, mid;
		Node *son[2];
		Node( i32 _left, i32 _rig ) : left(_left), rig(_rig), mid( ( _left + _rig ) >> 1 ) { 
			son[0] = son[1] = 0;
			seg = 0;
		}

		Node* get_son( int k ) {
			if( son[k] ) 
				return son[k];
			if( k == 0 ) 
				son[0] = new Node( left, mid );
			else
				son[1] = new Node( mid + 1, rig );
			return son[k];
		}
		double get_x( int x ) {
			if( seg ) 
				return seg -> get_x(x);
			else 
				return -DINF;
		}
	} *rt;

	SegmentTree( int _n ) { rt = new Node( 0, _n - 1 ); }

	double get( Node *cur, int p ) {
		if( cur -> left == cur -> rig ) 
			return cur -> get_x(p);
		if( p <= cur -> mid )
			return Max( cur -> get_x(p), get( cur -> get_son(0), p ) );
		else 
			return Max( cur -> get_x(p), get( cur -> get_son(1), p ) );
	}

	double get( int p ) { return get( rt, p ); }

	void update( Node *cur, Segment *seg ) {
		ci32 mid = cur -> mid;
		ci32 left = cur -> left;
		ci32 rig = cur -> rig;
		if( seg -> get_x(mid) >= cur -> get_x(mid) ) 
			std::swap( cur -> seg, seg );
		if( seg == 0 ) 
			return ;
		if( seg -> get_x(left) > cur -> get_x(left) ) 
			update( cur -> get_son(0), seg );
		if( seg -> get_x(rig) > cur -> get_x(left) ) 
			update( cur -> get_son(1), seg );
	}
	void update( Segment *seg ) {
		update( rt, seg );
	}
};

int main() {
#ifdef woshiluo
	freopen( "luogu.2523.in", "r", stdin );
	freopen( "luogu.2523.out", "w", stdout );
#endif

	ci32 n = read<i32>();
	ci32 s = read<i32>();
	std::vector<double> a, b, k, x, y;
	for( int i = 1; i <= n; i ++ ) {
		double t1, t2, t3;
		scanf( "%lf%lf%lf", &t1, &t2, &t3 );
		a.push_back(t1);
		b.push_back(t2);
		k.push_back(t3);
		list.push_back( a.back() / b.back() );
	}
	std::sort( list.begin(), list.end() );
	list.erase( std::unique( list.begin(), list.end() ), list.end() );
	std::vector<double> f(n);
	f[0] = s;
	auto get_x = [&] ( i32 cur ) { return f[cur] * k[cur] / ( a[cur] * k[cur] + b[cur] ); };
	auto get_y = [&] ( i32 cur ) { return f[cur] / ( a[cur] * k[cur] + b[cur] ); };
	x.push_back( get_x(0) );
	y.push_back( get_y(0) );
	SegmentTree *sgt = new SegmentTree(list.size());
	sgt -> update( new SegmentTree::Segment( x[0], y[0] ) );
	for( int  i = 1; i < n; i ++ ) {
		int p = std::lower_bound( list.begin(), list.end(), a[i] / b[i] ) - list.begin();
		f[i] = b[i] * sgt -> get(p);
		chk_Max( f[i], f[ i - 1 ] );
		x.push_back( get_x(i) );
		y.push_back( get_y(i) );
		sgt -> update( new SegmentTree::Segment( x[i], y[i] ) );
	}
	printf( "%.5lf\n", f.back() );
	
}
