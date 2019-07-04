#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 101000; 
const int mod = 201314;

inline int add(int a, int b){a += b;return a >= mod? a - mod: a;}
inline int sub(int a, int b){a -= b;return a < 0? a + mod: a;}

int ksm(int a, int p){
	int res = 1;
	while(p){
		if(p & 1)
			res = (1LL * res * a) % mod;
		a = (1LL * a * a) % mod;
		p >>= 1;
	}
	return res;
}

int n, Q, k;
int son[N], mson[N], dep[N], fa[N], top[N], id[N], ori[N], idcnt;

// edge start
struct edge{
	int to, next;
}e[N];
int ehead[N], ecnt;
inline void add_edge(int now, int to){
	ecnt ++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end

// Segment Tree Start
struct node{
	int base, sum, lazy;
}tree[N << 2];
inline void pushup(int now){ tree[now].sum = add(tree[now << 1].sum, tree[now << 1|1].sum); }
inline void pushdown(int now){
	if(tree[now].lazy){
		tree[now << 1].sum = add((1LL * tree[now].lazy * tree[now << 1].base) % mod, tree[now << 1].sum);
		tree[now << 1|1].sum = add((1LL * tree[now].lazy * tree[now << 1|1].base) % mod, tree[now << 1|1].sum);
		tree[now << 1].lazy += tree[now].lazy;
		tree[now << 1|1].lazy += tree[now].lazy;
		tree[now].lazy = 0;
	}
}

void build_tree(int now = 1, int left = 1, int rig = n){
	if(left == rig){
		tree[now].base = sub(ksm(dep[ ori[left] ], k), ksm(dep[ ori[left] ] - 1, k));
		return ;
	}
	int mid = (left + rig) >> 1;
	build_tree(now << 1, left, mid);
	build_tree(now << 1|1, mid + 1, rig);
	tree[now].base = add(tree[now << 1].base, tree[now << 1|1].base);
}

void query_add(int from, int to, int val = 1, int now = 1, int left = 1, int rig = n){
	if(from <= left && rig <= to){
		tree[now].sum = add(tree[now].sum, tree[now].base);
		tree[now].lazy ++;
		return ;
	}
	pushdown(now);
	int mid = (left + rig) >> 1;
	if(from <= mid) 
		query_add(from, to, val, now << 1, left, mid);
	if(to > mid) 
		query_add(from, to, val, now << 1|1, mid + 1, rig);
	pushup(now);
}

int query_sum(int from, int to, int now = 1, int left = 1, int rig = n){
	if(from <= left && rig <= to)
		return tree[now].sum;
	pushdown(now);
	int mid = (left + rig) >> 1, res = 0;
	if(from <= mid) 
		res = add(res, query_sum(from, to, now << 1, left, mid));
	if(to > mid) 
		res = add(res, query_sum(from, to, now << 1|1, mid + 1, rig));
	return res;
}
// Segment Tree End

// Heavy-Light Depostion Start
void dfs1(int now = 1){
	son[now] = 1;
	for(int i = ehead[now]; i; i = e[i].next){
		dep[ e[i].to ] = dep[now] + 1;
		fa[ e[i].to ] = now;
		dfs1(e[i].to);	
		son[now] += son[ e[i].to ];
		if( son[ e[i].to ] > son[ mson[now] ] )
			mson[now] = e[i].to;
	}
}

void dfs2(int now = 1){
	id[now] = ++idcnt; ori[idcnt] = now;
	if(top[now] == 0)
		top[now] = now;
	if(mson[now] == 0)
		return ;
	top[ mson[now] ] = top[now];
	dfs2(mson[now]);
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == mson[now])
			continue;
		dfs2(e[i].to);
	}
}

void line_add(int from, int to = 1){
	while(top[from] != top[to]){
		if(dep[ top[from] ] < dep[ top[to] ]){ int tmp = from; from = to; to = tmp; }
		query_add(id[ top[from] ], id[ from ]);
		from = fa[ top[from] ];
	}	
	if(id[from] > id[to]){ int tmp = from; from = to; to = tmp; }
	query_add(id[from], id[to]);	
}

int line_sum(int from, int to = 1){
	int res = 0;
	while(top[from] != top[to]){
		if(dep[ top[from] ] < dep[ top[to] ]){ int tmp = from; from = to; to = tmp; }
		res = add(res, query_sum(id[ top[from] ], id[ from ]));
		from = fa[ top[from] ];
	}	
	if(id[from] > id[to]){ int tmp = from; from = to; to = tmp; }
	res = add(res, query_sum(id[from], id[to]));	
	return res;
}
// Heavy-Light Depostion End

// ask start
struct ques{
	int x, y, id;
	bool operator< (const ques &b) const{ return this->x < b.x; }
}ask[N];
int ans[N];
void calc(){
	std::sort(ask + 1, ask + Q + 1);

	build_tree();
	for(int i = 1; i <= Q; i++){
		for(int j = ask[i - 1].x + 1; j <= ask[i].x; j++)
			line_add(j);
		ans[ ask[i].id ] = line_sum(ask[i].y);
	}
}
// ask end
int main(){
#ifdef woshiluo
	freopen("luogu.4211.in", "r", stdin);
	freopen("luogu.4211.out", "w", stdout);
#endif
	scanf("%d%d", &n, &Q);
	k = 1;
	for(int i = 1, tmp; i < n; i++){
		scanf("%d", &tmp);	
		tmp ++;
		add_edge(tmp, i + 1);
	}
	for(int i = 1, left, rig, z; i <= Q; i++){
		scanf("%d%d%d", &left, &rig, &z);
		ask[(i << 1) - 1].id = (i << 1) - 1;
		ask[i << 1].id = i << 1;
		ask[(i << 1) - 1].x = left;
		ask[i << 1].x = rig + 1;
		ask[i << 1].y = ask[(i << 1) - 1].y = z + 1;
	}

	Q <<= 1;
	dep[1] = 1;
	dfs1();
	dfs2();

	calc();

	Q >>= 1;
	for(int i = 1; i <= Q; i++)
		printf("%d\n", sub(ans[i << 1], ans[(i << 1) - 1]));

	return 0;
}
