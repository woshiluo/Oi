// Woshiluo Luo<woshiluo@woshiluo.site>  
// 2020/03/11 17:02:05 
#include <cstdio>
#include <cstring>

#include <set>
#include <algorithm>

template<class T>
T Min( T _a, T _b ) { return _a < _b? _a: _b; }
template<class T>
T Max( T _a, T _b ) { return _a > _b? _a: _b; }
template<class T>
T chk_Min( T &_a, T _b ) { return _a = (_a < _b? _a: _b); }
template<class T>
T chk_Max( T &_a, T _b ) { return _a = (_a > _b? _a: _b); }

int n, m;

namespace io {/*{{{*/
	int seed, vmax;
	inline int rnd() {
		int ret = seed;
		seed = ( seed * 7 + 13 ) % 1000000007;
		return ret;
	}
	int* get_a() {
		int *tmp = new int[ n + 1 ];
		for( int i = 1; i <= n; i ++ ) {
			*( tmp + i ) = ( rnd() % vmax ) + 1;
		}
		return tmp;
	}
	int* get_op() {
		int *tmp = new int[5];
		int &op = tmp[0], &l = tmp[1], &r = tmp[2], &x = tmp[3], &y = tmp[4];
		op = ( rnd() % 4 ) + 1;
		l = ( rnd() % n ) + 1;
		r = ( rnd() % n ) + 1;
		if( l > r ) 
			std::swap( l, r );

		if( op == 3 ) {
			x = ( rnd() % ( r - l + 1 ) ) + 1;
		}
		else {
			x = ( rnd() % vmax ) + 1;
		}

		if( op == 4 ) {
			y = ( rnd() % vmax ) + 1;
		}
		return tmp;
	}
}/*}}}*/

struct node_t {
	int l, t;
	mutable val;
	node( int _l, int _r = -1, long long _val = 0 ) {
		l = _l, r = _r, val = _val;
	}
	bool operator< (const node b) {
		return l < a.l;
	}
};

int main() {
	scanf( "%d%d%d%d", &n, &m, &io::seed, &io::vmax );
	int *a = io::get_a();
	for( int i = 1; i <= n; i ++ ) {
		assign( i, i, a[i] );
	}
}
