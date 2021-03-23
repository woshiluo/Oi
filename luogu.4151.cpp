#include <cstdio>
#include <cstring>

#include <vector>

const int N = 5e4 + 1e3;
const int M = N << 1;

typedef long long ll;
typedef unsigned long long ull;

inline bool has_bit( ull a, ull k ) { return a & ( 1ull << k ); }

// Edge Start 
struct edge{ 
	int to, next;
	ll val;
} e[ M << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to, ll val ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// Edge End

const int MAX_LENGTH = 63;
struct LinearBasis {
	int n = 0;
	std::vector<ll> v;
	ll a[MAX_LENGTH];
	
	inline void init( int _n ) {
		n = _n;
		v.clear();
		memset( a, 0, sizeof(a) );
	}

	void update() {
		v.clear();
		for( int i = 0; i < MAX_LENGTH; i ++ ) {
			if( a[i] != 0 ) 
				v.push_back( a[i] );
		}
	}

	void add( ll cur ) {
		for( int k = MAX_LENGTH - 1; k >= 0; k --  ) {
			if( cur == 0 ) 
				return ;
			if( has_bit( cur, k ) == false )
				continue;
			if( a[k] ) {
				cur ^= a[k];
				continue;
			}
			
			for( int i = 0; i < k; i ++ ) {
				if( has_bit( cur, i ) ) 
					cur ^= a[i];
			}

			for( int i = k + 1; i < MAX_LENGTH; i ++ ) {
				if( has_bit( a[i], k ) ) 
					a[i] ^= cur;
			}

			a[k] = cur;
			break;
		}
	}

	ll query( ll res ) {
		for( auto x: v ) {
			if( ( res ^ x ) > res ) 
				res = ( res ^ x );
		}
		return res;
	}
} linearbasis;

ll dis[N];
void dfs( int cur, int fa, ll val ) {
	dis[cur] = val;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == fa ) 
			continue;
		if( dis[ e[i].to ] != 0 ) 
			linearbasis.add( dis[ e[i].to ] ^ val ^ e[i].val );
		else {
			dfs( e[i].to, cur, val ^ e[i].val );
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "luogu.4151.in", "r", stdin );
	freopen( "luogu.4151.out", "w", stdout );
#endif
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		static int u, v; 
		static ull w;
		scanf( "%d%d%llu", &u, &v, &w );
		add_edge( u, v, w );
		add_edge( v, u, w );
	}

	dfs( 1, 0, 0 );
	linearbasis.update();

	printf( "%lld\n", linearbasis.query( dis[n] ) );
}
