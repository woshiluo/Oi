#include <cstdio>

const int N = 1100;
const int M = N * N;

struct Con {
	int left, rig;
} con[ M << 1 ];

struct edge {
	int to, next;
} e[ M << 1 ];
int ehead[N], ecnt;
inline void add_edge( int cur, int to ) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[cur];
	ehead[cur] = ecnt;
}
// *0 woman
// *1 man

int n, m;

int main() {
	scanf( "%d%d", &n, &m );
	for( int i = 1; i <= m; i ++ ) {
		int a1, a2, c1, c2;
		scanf( "%d%d%d%d", &a1, &a2, &c1, &c2 );
		con[i] = (Con) { ( a1 * 2 ) ^ c1, ( a1 * 2 ) ^ c2 };
		add_edge( con[i].left, con[i].rig ^ 1 );
		add_edge( con[i].left ^ 1, con[i].rig );
	}
}
