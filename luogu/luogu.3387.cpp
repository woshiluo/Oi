#include <cstdio>

struct Graph {
	struct edge {
		int to, next;
	} e[ M ];
	int ehead[N], ecnt;
	inline void add_edge( int cur, int to ) {
		ecnt ++;
		e[ecnt].to = to;
		e[ecnt].next = ehead[cur];
		ehead[cur] = ecnt;
	}
	inline void get_st( int cur ) {
		return ehead[cur];
	}
}

int dfn[N], low[N], time_index;
int col[N];

int main() {
}
