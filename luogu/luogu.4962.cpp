#include <cstdio>
#include <cstring>

#include <vector>

template<class T>
inline void chk_Min( T &a, T b ) { if( a > b ) a = b; } 

// inline int readin() {
// 	int res = 0; char x = getchar();
// 	while( x > '9' || x < '0' ) 
// 		x = getchar();
// 	while( x >= '0' && x <= '9' ) {
// 		res = res * 10 + ( x - '0' );
// 		x = getchar();
// 	}
// 	return res;
// }

const int N = 102;
const int M = N * N;
const int K = 1 << 15;
const int INF = 0x3f3f3f3f;

// struct edge { int to, next, val; };

int n, m, k;
short a[N];
int f[N][K];

// Edge Start
int fn[N][N];
// edge e[M];
// int ehead[N], ecnt;
// inline void add_edge( int cur, int to, int val ) {
// 	ecnt ++;
// 	e[ecnt].to = to;
// 	e[ecnt].next = ehead[cur];
// 	e[ecnt].val = val;
// 	ehead[cur] = ecnt;
// }
// Edge End

// Bit change 
inline unsigned int full_bit( int k ) { return 1 << k; }
inline unsigned int has( int k, int a ) { return ( k >> a ) & 1; }
inline unsigned int add( int k, int a ) { return k | ( 1 << a ); }
// inline int len( int k ) {
// 	int res = 0;
// 	while( k ) {
// 		k /= 2;
// 		res += ( k & 1 );
// 	}
// 	return res;
// }


std::vector<int> kind[14];
int main() {
#ifdef woshiluo
	freopen( "luogu.4962.in", "r", stdin );
	freopen( "luogu.4962.out", "w", stdout );
#endif
	scanf( "%d%d%d", &n, &m, &k );
	//	n = readin(); m = readin(); k = readin();
	for( int i = 1; i <= n; i ++ ) {
		scanf( "%hd", &a[i] );
		kind[ a[i] ].push_back(i);
		//		a[i] = readin();
	}
	for( int i = 1; i <= m; i ++ ) {
		int u, v, w;
		scanf( "%d%d%d", &u, &v, &w );
		fn[u][v] = w;
		//		u = readin(); v = readin(); w = readin();
		//		add_edge( u, v, w );
	}

	memset( f, INF, sizeof(f) );
	for( int i = 1; i <= n; i ++ ) {
		f[i][ add( 0, a[i] ) ] = 0; 
	}

	for( int _o = 1; _o < k; _o ++ ) {
		int full_k = full_bit(k);
		for( int j = 0; j < full_k; j ++ ) {
			for( int k_i = 0; k_i < k; k_i ++ ) {
				if( has( j, k_i ) == false )
					continue;
				for( auto &i: kind[k_i] ) {
					if( f[i][j] >= INF )
						continue;
					for( int k_j = 0; k_j < k; k_j ++ ) {
						if( has( j, k_j ) )
							continue;
						for( auto &to: kind[k_j] ) {
							int val = fn[i][to];
							if( val == 0 )
								continue;
							chk_Min<int>( f[to][ add( j, a[to] ) ], f[i][j] + val );
						}
					}
				}
			}
		}
	}

	int res = INF, full = full_bit(k) - 1;
	for( int i = 1; i <= n; i ++ ) {
		chk_Min<int>( res, f[i][full] );
	}

	if( res >= INF ) {
		printf( "Ushio!" );
	}
	else {
		printf( "%d", res );
	}
}
