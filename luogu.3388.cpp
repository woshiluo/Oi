#include <cstdio>
#include <cstring>

inline int Min(int a, int b) {return a < b? a: b;}

const int N = 2e4 + 1e4;
const int M = 1e5 + 1e4;

int n, m;

// Edge Start 
struct edge {
	int to, next;
} e[M << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to) {
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// Edge End

// Tarjan Start 
int dfn[N], low[N], time_index, son;
bool cut[N];

void tarjan(int now, bool st){
	dfn[now] = low[now] = ++ time_index;
	if(st) 
		son = 0;
	for(int i = ehead[now]; i; i = e[i].next) {
		if( dfn[ e[i].to ] == 0 ){
			tarjan( e[i].to, false);
			low[now] = Min(low[now], low[ e[i].to ]);
			if( low[ e[i].to ] >= dfn[now] && !st )
				cut[now] = true;
			son += st;
		}
		else 
			low[now] = Min(low[now], dfn[ e[i].to ]);
	}
	if( st && son >= 2 )
		cut[now] = true;
}

void _tarjan() {
	for(int i = 1; i <= n; i++) {
		if( dfn[i] == 0 ) 
			tarjan(i, true);
	}
}
// Tarjan End

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	
	_tarjan();
	
	int cnt = 0;
	for(int i = 1; i <= n; i++)
		cnt += cut[i];

	printf("%d\n", cnt);

	for(int i = 1; i <= n; i++) 
		cut[i] && printf("%d ", i);
}
