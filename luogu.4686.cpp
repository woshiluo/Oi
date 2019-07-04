#include <cstdio>

#include <algorithm>

const int N = 1100000;

struct _seg {
	int left, rig;
} seg[N];

struct _node {
	int x, pos;	
	bool left;
	bool operator< (_node b) {
		return this -> x < b.x;
	}
} node[N << 1];

int n, m, ans;
int node_cnt, cir_cnt;
int size[N];
bool vis[N << 1];

bool cmp(int a, int b) {
	return a > b;
}

inline int find(int now) { return std::lower_bound( node + 1, node + node_cnt + 1, (_node){now, 0, 0} ) - node; } 

void dfs(int now, int pos) {
	while( vis[now] == false ) {
		vis[now] = true;
		size[pos] ++;
		if( node[now].left ) now = find( seg[ node[now].pos ].rig + 1 );
		else now = find( seg[ node[now].pos ].left + 1 );
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf("%d%d", &seg[i].left, &seg[i].rig);
		node[ ++ node_cnt ] = (_node) { seg[i].left, i, true };
		node[ ++ node_cnt ] = (_node) { seg[i].rig, i, false };
	}

	std::sort( node + 1, node + node_cnt + 1 );

	int cur = 1;
	while( cur != node_cnt + 1 ) {
		ans ++;
		vis[cur] = true;
		if( node[cur].left ) cur = find( seg[ node[cur].pos ].rig + 1 );
		else cur = find( seg[ node[cur].pos ].left + 1 );
	}

	vis[cur] = true;
	for(int i = 1; i <= node_cnt; i++) {
		if( vis[i] == false ) 
			dfs(i, ++ cir_cnt);
	}

	std::sort(size + 1, size + cir_cnt + 1, cmp);
	
	for(int i = 1; i <= cir_cnt && m; i++) {
		ans += 2;
		ans += size[i];
		m --;
	}

	if(m) {
		if( m & 1 ) {
			m --; 
			ans ++;
		}
		ans += m << 1;
	}
	
	printf("%d", ans);
}
