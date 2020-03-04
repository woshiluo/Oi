#include <cstdlib>
#include <ctime>

#include <algorithm> 

const int N = 1100;

int n;

// Edge Start 
struct edge {
	int to, next;
} e[ N << 1 ];
int ehead[N], ecnt;
inline void add_edge( int now, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

int test_fa[N], dep[N];
int rt;

void test_dfs( int cur, int la ) {
	test_fa[cur] = la;
	dep[cur] = dep[la] + 1;
	for( int i = ehead[cur]; i; i = e[i].next ) {
		if( e[i].to == la ) 
			continue;
		test_dfs( e[i].to, cur );
	}
}

void test_init() {
	srand( time(0) );
	rt = rand() % n + 1;
//	rt = 15;
	test_dfs( rt, 0 );
}


void chk_rt( int cur ){
	if( cur == rt ) 
		printf( "Right! Answer: %d, Output: %d", rt, cur );
	else 
		printf( "Wrong! Answer: %d, Output: %d", rt, cur );
	exit(0);
}

int test_cnt = 0;
int ask( int u, int v ) {
	test_cnt ++;
	if( test_cnt > n / 2 ) {
		printf( "Disallowed!!!" );
		exit(0);
	}
	printf( "%d: %d %d\n", test_cnt, u, v );
	while( u != v ) {
		if( dep[u] < dep[v] ) 
			std::swap( u, v );
		u = test_fa[u];
	}
	printf( "%d\n", u );
	return u;
}
