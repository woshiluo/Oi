/*
 * e.cpp
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

#include <set>
#include <vector>
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

const int N = 1e6 + 1e5;

std::vector<ll> sum[N];


struct odt {
	struct Node {
		int left, rig;
		mutable int last;
		mutable ll val;
		mutable int col;

		Node( int _left = 0 ) { 
			left = rig = _left;
			last = val = col = 0;
		}
		Node( int _left, int _rig, int _last, ll _val, int _col ) { left = _left; rig = _rig; last = _last; val =  _val; col = _col; }
		bool operator< ( const Node &_b ) const { return left < _b.left; }
		void update() const {
			val += sum[col].back() - sum[col][last];
			last = sum[col].size() - 1;
		}
	};
	std::set<Node> set;

	auto split( int x ) {
		auto iter = set.upper_bound( Node(x) );
		iter --;
		if( iter -> left == x ) 
			return iter;

		iter -> update();
		auto left = *iter, rig = *iter;
		left.rig = x - 1; rig.left = x;
		set.erase(iter);
		set.insert(left);
		return set.insert(rig).first;
	}

	void assign( int left, int rig ) {
		auto itr = split( rig + 1 );
		auto itl = split(left);
		itl -> update(); itr -> update();
		auto node = *itl; node.left = left; node.rig = rig;
		set.erase( itl, itr );
		set.insert( node );
	}

//	void performancce( int left, int rig ) {
//		auto itl = split(left), itr = split( rig + 1 );
//		for( auto it = itl; it != itr ; it ++ ) {
//			it -> update();
//		}
//	}
} odt;

int main() {
#ifdef woshiluo
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
#endif
	int n, q;
	n = read<int>(); q = read<int>();
	odt.set.insert( (odt::Node) { 1, n, 0, 0, 1} );
	for( int i = 1; i <= n; i ++ ) {
		sum[i].push_back(0);
	}
	while( q -- ) {
		char op[10];
		scanf(  "%s", op );
		if( op[0] == 'C' ) {
			int x, y, z;
			x = read<int>(); y = read<int>(); z = read<int>();
			odt.assign( x, y );
			auto cur = odt.split(x);
			cur -> update();
			cur -> col = z;
			cur -> last = sum[z].size() - 1;
		}
		if( op[0] == 'A' ) {
			int x, y;
			x = read<int>(); y = read<int>();
			ll cur = sum[x].back() + 1LL * y;
			sum[x].push_back(cur);
		}
		if( op[0] == 'Q' ) {
			int x = read<int>();
			auto cur = odt.split(x);
			printf( "%lld\n", cur -> val );
		}
	}
}
