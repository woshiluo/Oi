#include <cstdio>

#include <map>
#include <vector>
#include <algorithm>

const int N = 1e5 + 1e4;
const int mod = 1e9 + 7;

int n;
int h[N], w[N], la[N];
long long sum[N], f[N];
std::map<int, int> mp;

template<class T, class Q>
inline int add( T a, Q b ) { return ( a + b ) % mod; }
template<class T, class Q>
inline int mul( T a, Q b ) { return ( 1LL * a * b ) % mod; }
inline int seq( int _a ) { 
	int a = ( _a + 1 ), b = _a;
	return mul( a, mul( b, 500000004 ) );
}

inline int calc_cur( int _a, int _b ) {
	return mul( seq( _a ), seq( _b ) );
}

struct SegmentTree {
	int tree[ N << 2 ];
	inline void push_up( int cur ) {
		tree[cur] = std::max( tree[ cur << 1 ], tree[ cur << 1 | 1 ] );
	}
	void build( int cur, int left, int rig ) {
		if( left == rig ) {
			tree[cur] = 0;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		build( cur << 1, left, mid );
		build( cur << 1 | 1, mid + 1, rig );
		push_up(cur);
	}
	void update( int pos, int val, int cur, int left, int rig ) {
		if( left == rig ) {
			if( left == pos ) 
				tree[cur] = val;
			return ;
		}

		int mid = ( left + rig ) >> 1;
		if( pos <= mid )
			update( pos, val, cur << 1, left, mid );
		else
			update( pos, val, cur << 1 | 1, mid + 1, rig );

		push_up(cur);
	}
	int query( int from, int to, int cur, int left, int rig ) {
		if( from <= left && rig <= to ) {
			return tree[cur];
		}

		// FIXME: res = INF or 0 ?
		int mid = ( left + rig ) >> 1, res = 0;
		if( from <= mid ) 
			res = std::max( res, query( from, to, cur << 1, left, mid ) );
		if( to > mid ) 
			res = std::max( res, query( from, to, cur << 1 | 1, mid + 1, rig ) );

		return res;
	}
};

int main() {
#ifdef woshiluo
	freopen( "a.in", "r", stdin );
	freopen( "a.out", "w", stdout );
#endif
	scanf( "%d", &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &h[i] );
		mp[ h[i] ] = 1;
	}
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d", &w[i] );
		sum[i] = sum[ i - 1 ] + w[i];
	}

	// 离散
	std::vector<int> rk;
	{
		rk.push_back(0);
		for( auto x: mp ) {
			rk.push_back( x.first );
		}
		int size = rk.size();
		for( int i = 1; i < size; i ++ ) {
			mp[ rk[i] ] = i;
		}
		for( int i = 1; i <= n; i ++ ){
			h[i] = mp[ h[i] ];
		}
	}

	// Get ans
	int ans = 0;
	{
		SegmentTree seg;
		seg.build( 1, 1, n );
		for( int i = 1; i <= n; i ++ ) {
			int last = seg.query( 1, h[i], 1, 1, n ), trans = 0, 
				rig_border = mul( seq( rk[ h[i] ] ), w[i] );
			if( last ) {
				trans = add( f[ last ], 
								mul( seq( rk[ h[i] ] ), 
									add( sum[ i - 1 ], - sum[ last ] ) ) );
				f[i] = add( trans, rig_border ); 
			}
			else {
				trans = mul( seq( rk[ h[i] ] ), add( sum[ i - 1 ], - sum[ last ] ) );
				f[i] = add( trans, rig_border );
			}
			ans = add( ans, f[i] - rig_border );
			ans = add( ans, mul( trans, w[i] - 1 ) );
			ans = add( ans, calc_cur( rk[ h[i] ], w[i] ) );
			seg.update( h[i], i, 1, 1, n );
		}
	}
	
	printf( "%d\n", ( ans + mod ) % mod );
}
