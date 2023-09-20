#include <cstdio>

inline int lowbit(int now){return now & (-now);}

const int N = 110000;

int m, u, v, tcnt, now, tmp, end_cnt;
int aid[N], ans[N];
char str[N];

// edge start 
struct edge{
	int next, to;
}e[N<<1], ae[N];
int ehead[N], aehead[N], ecnt, aecnt;
inline void add_edge(int now, int to, int &ecnt, int *ehead, edge *e){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

// BIT start 
int tree[N],res;
inline int sum(int now){
	res=0;
	for(; now; now -= lowbit(now)) res += tree[now];
	return res;
}
inline void add(int now,int val){
	for(; now <= tcnt + 1; now += lowbit(now)) tree[now] += val;
}
// BIT end

// Fail Tree start 
int root, head, tail;
int end[N], fail[N], q[N], fa[N], id[N], trie[N][28];
inline void insert(char str){
	tmp = str - 'a';	
	if(trie[now][tmp] == 0) trie[now][tmp] = ++tcnt;
	fa[ trie[now][tmp] ] = now;
	now = trie[now][tmp];
}

inline void make_fail_tree(){
	head = tail = 0;
	q[head] = fail[root] = root;

	for(int i = 0; i < 26; i++)
		if(trie[root][i])
			q[tail++] = trie[root][i],fail[ trie[root][i] ] = root;

	tail--;

	while(head <= tail){
		for(int i = 0; i < 26; i++){
			if( trie[ q[head] ][i] ){
				tmp = fail[ q[head] ];
				while(trie[tmp][i] == 0 && tmp) tmp = fail[tmp];
				fail[ trie[ q[head] ][i] ] = trie[tmp][i];
				q[ ++tail ] = trie[ q[head] ][i];
			}
		}
		head++;
	}
}
// Fail Tree end
int time;
int dfn[N], size[N];
void dfs_fail(int now,int la){
	size[now] = 1;
	dfn[now] = ++time;
	for(int i = ehead[now]; i; i=e[i].next){
		if(e[i].to == la) continue;
		dfs_fail(e[i].to, now);
		size[now] += size[ e[i].to ];
	}
}

void dfs_trie(int now){
	add(dfn[now], 1);
	if(end[now])
		for(int i = aehead[ end[now] ]; i; i = ae[i].next)
			ans[ aid[i] ] = sum(dfn[ id[ ae[i].to ] ] + size[ id[ ae[i].to ] ] - 1) - sum(dfn[ id[ ae[i].to ] ] - 1);
	for(int i = 0; i < 26; i++)
		if( trie[now][i] ) 
			dfs_trie(trie[now][i]);
	add(dfn[now], -1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("luogu.2414.in", "r", stdin);
	freopen("luogu.2414.out", "w" ,stdout);
#endif
	while(tmp = getchar()){
		if(tmp == '\n') break;
		if(tmp == 'B') now = fa[now];
		else if(tmp == 'P') end[now] = ++end_cnt, id[end_cnt] = now;
		else insert(tmp);
	}

	make_fail_tree();

	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		scanf("%d%d", &u, &v);
		add_edge(v, u, aecnt, aehead, ae);
		aid[aecnt] = i;
	}
	for(int i = 1;i <= tcnt; i++){
		add_edge(i, fail[i], ecnt, ehead, e);
		add_edge(fail[i], i, ecnt, ehead, e);
	}

	dfs_fail(root, 0);
	dfs_trie(root);

	for(int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}
