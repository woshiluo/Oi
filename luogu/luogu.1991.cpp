#include <cmath>
#include <cstdio>

#include <algorithm>

const double eps = 1e-4;
const int N = 1100;

inline void chk_Max( double &a, double b ) { a = std::max( a, b ); }

struct node { int x, y; };

struct Set {
	int fa[N];
	Set( int max = 1 ) {
		for( int i = 0; i <= max; i ++ ) {
			fa[i] = i;
		}
	}
	inline int& get_fa( int cur ) {
		if( fa[cur] == cur ) 
			return fa[cur];
		int *p = &get_fa(fa[cur]);
		fa[cur] = *p;
		return *p;
	}
	inline int& operator[] ( int cur ) {
		return get_fa(cur);
	}
};

inline double pow_2( double cur ) { return cur * cur; }
inline double dis( node x, node y ) {
	return std::sqrt( pow_2( y.x - x.x ) + pow_2( y.y - x.y ) );
}

int k, n;
node a[N];

bool check( double gol ) {
	Set set(n);
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			if( set[i] != set[j] && dis( a[i], a[j] ) + eps <= gol )
				set[i] = set[j];
		}
	}
	int cnt = 0;
	for( int i = 1; i <= n; i ++ ) 
		cnt += ( set[i] == i );
	return cnt <= k;
}

int main() {
#ifdef woshiluo
	freopen( "luogu.1991.in", "r", stdin );
	freopen( "luogu.1991.out", "w", stdout );
#endif
	scanf( "%d%d", &k, &n );
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%d%d", &a[i].x, &a[i].y );
	}

	double left = 0, rig = 0;
	for( int i = 1; i <= n; i ++ ) {
		for( int j = 1; j <= n; j ++ ) {
			chk_Max( rig, dis( a[i], a[j] ) );
		}
	}

	double res = rig;
	while( left + eps <= rig ) {
		double mid = ( left + rig ) / 2.0;
		if( check(mid) ) {
			res = mid;
			rig = mid - eps;
		}
		else 
			left = mid + eps;
	}

	printf( "%.2lf", res );
}
