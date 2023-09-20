#include <cstdio>

#include <queue>
#include <vector>

const int N = 310;
const int NN = N * N;
const double eqs = 1e-12;

inline double aabs( double a ) { return a < 0? -a: a; }

struct ACAM {
	const int rt = 0;
	int node_cnt = 0;
	struct node {
		int val, fail, nxt[2];
		bool ed;
		std::vector<int> vis;
		node() {
			val = ed = false;
			nxt[0] = nxt[1] = fail = 0;
		}
	} tree[NN];
	int ed[N], dep[NN];
	void insert( int id, char str[] ) {
		int cur = rt;
		for( ; *str != 0; str ++ ) {
			tree[cur].vis.push_back(id);
			int val = *str == 'H'? 1: 0;
			if( tree[cur].nxt[val] == 0 ) {
				node_cnt ++;
				dep[node_cnt] = dep[cur] + 1;
				tree[cur].nxt[val] = node_cnt;
			}
			cur = tree[cur].nxt[val];
		}
		tree[cur].vis.push_back(id);
		tree[cur].ed = true;
		ed[id] = cur;
	}
	void build() {
		std::queue<int> q;
		for( int i = 0; i < 2; i ++ ) {
			if( tree[rt].nxt[i] != 0 ) 
				q.push( tree[rt].nxt[i] );
		}
		while( !q.empty() ) {
			int cur = q.front(); q.pop();
			for( int i = 0; i < 2; i ++ ) {
				int nxt = tree[cur].nxt[i];
				int fail = tree[cur].fail;
				if( nxt ) {
					tree[nxt].fail = tree[fail].nxt[i];
					q.push(nxt);
				}
				else {
					tree[cur].nxt[i] = tree[fail].nxt[i];
				}
			}
		}
	}
	void gen_gauss( double f[N][N], int n, int m ) {
		double pow_2[N];
		pow_2[0] = 1.0;
		for( int i = 1; i <= m; i ++ ) { 
			pow_2[i] = pow_2[ i - 1 ] * 2.0;
		}
		for( int i = 1; i <= n; i ++ ) {
			int cur = ed[i];
			while(1) {
				for( auto x: tree[cur].vis ) {
					f[x][i] += pow_2[ dep[cur] ];
				}
				if( cur == tree[cur].fail ) 
					break;
				cur = tree[cur].fail;
			}
			f[i][ n + 1 ] = - 1.0;
		}
		for( int i = 1; i <= n; i ++ ) 
			f[ n + 1 ][i] = 1;
		f[ n + 1 ][ n + 2 ] = 1;
	}
} ac;

double A[N][N];

void gauss( double f[N][N], int n ) {
	for( int i = 1; i <= n; i ++ ) {
		int t = i;
		for( int j = i; j <= n; j ++ ) {
			if( aabs( f[j][i] ) > aabs( f[t][i] ) )
				t = j;
		}
		for( int j = i; j <= n + 1; j ++ ) {
			std::swap( f[i][j], f[t][j] );
		}
		for( int j = n + 1; j >= i; j -- ) 
			f[i][j] /= f[i][i];
		for( int j = 1; j <= n; j ++ ) {
			if( i == j ) 
				continue;
			for( int k = n + 1; k >= i; k -- ) {
				f[j][k] -= f[j][i] * f[i][k];
			}
		}
	}
}

int main() {
#ifdef woshiluo
	freopen( "loj.2004.in", "r", stdin );
	freopen( "loj.2004.out", "w", stdout );
#endif
	int n, m;
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= n; i ++ ) {
		char str[N];
		scanf( "%s", str );
		ac.insert( i, str );
	}
	ac.build();

	ac.gen_gauss( A, n, m );

	gauss( A, n + 1 );

	for( int i = 1; i <= n; i ++ ) {
		printf( "%.10lf\n", A[i][ n + 2 ] );
	}
}
