#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

inline long long Max( long long a, long long b ) { return a > b? a: b; }

const int N = 11000;

int n;
long long dis[N], s[N];

// Edge Start
struct edge {
	int to, next, val;
} e[N];
int ehead[N], ecnt;
inline void add_edge( int now, int to, int val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	e[ecnt].val = val;
	ehead[now] = ecnt;
}
// Edge End

bool cmp( long long _a, long long _b ) { return _a > _b; }

void init() {
	ecnt = 0;
	memset( s, 0, sizeof(s) );
	memset( dis, 0, sizeof(dis) );
	memset( ehead, 0, sizeof(ehead) );
}

void readin() {
	for( int i = 2, w, v; i <= n; i ++ ) {
		scanf( "%d%d", &v, &w );
		add_edge( v, i, w );
	}
}

void dp( int now ) {
	for( int i = ehead[now]; i; i = e[i].next ) {
		dp( e[i].to );
		dis[now] = Max( dis[now], dis[ e[i].to ] + e[i].val );
	}
}

void dp2( int now, long long _max ) {
	std::vector<long long> a;
	for( int i = ehead[now]; i; i = e[i].next ) {
		a.push_back( dis[ e[i].to ] + e[i].val );
	}
	a.push_back(0); a.push_back(0);
	std::sort( a.begin(), a.end(), cmp );

	s[now] = Max( a[0], _max );

	long long tmp = Max( _max, a[0] );
	for( int i = ehead[now]; i; i = e[i].next ) {
		if( dis[ e[i].to ] + e[i].val == a[0] ) 
			dp2( e[i].to, Max( _max, a[1] ) + e[i].val );
		else 
			dp2( e[i].to, tmp + e[i].val );
	}
}

int main() {
#ifdef woshiluo
	freopen( "hdu.2196.in", "r", stdin );
	freopen( "hdu.2196.out", "w", stdout );
#endif
	while( scanf( "%d", &n ) != EOF ) {
		init(), readin(), dp( 1 ), dp2( 1, 0 );
		for( int i = 1; i <= n; i ++ ) {
			printf( "%lld\n", s[i] );
		}
	}
}
