#include <cstdio>

int n, m, r, p;

int son[N], fa[N], dep[N], mson[N];
void dfs1(int now, int la, int depth){
	son[now] = 1;
	dep[now] = depth; fa[now] = la;
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == la) 
			continue;
		dfs1(e[i].to, now, depth + 1);
		son[now] += son[ e[i].to ];
		if(son[ e[i].to ] > son[ mson[now] ]) 
			mson[now] = e[i].to;
	}
}

int top[N], id[N], idcnt;
void dfs2(int now, int fa){
	id[now] = ++idcnt;
	if(top[now] == 0)
		top[now] = now;
	if(mson[now] == 0) 
		return ;
	top[ mson[now] ] = top[now];
	dfs2(mson[now], now);
	for(int i = ehead[now]; i; i = e[i].next){
		if(e[i].to == fa || e[i].to == mson[now])
			continue;
		dfs2(e[i].to, now);
	}
}

int lca(int from, int to){
	while(top[from] != top[to]){
		if(dep[ top[from] ] < dep[ top[to] ]){ int tmp = from; from = to; to = tmp; }
		from = fa[ top[from] ];
	}
	return dep[from] < dep[to]? from: to;
}

int main(){
}
