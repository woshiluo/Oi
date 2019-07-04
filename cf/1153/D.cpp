#include <cstdio>
#include <algorithm>

inline int Max(int a, int b){return a > b? a: b;}
inline int Min(int a, int b){return a < b? a: b;}

const int N = 3e5 + 10;

int cnt;

struct node{
	int id, val;
}a[N];

bool cmp(node a, node b){
	return a.val < b.val;
}

int n;
int zf[N], qz[N], size[N], val[N];

struct edge{
	int to, next;
}e[N << 1];
int ehead[N], ecnt;

inline void add_edge(int now, int to){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}

void dfs1(int now, int val){
	size[now] = 1;
	qz[now] = val;
	if(zf[now] == 0) 
		val --;
	else
		val++;
	for(int i = ehead[now]; i; i = e[i].next){
		dfs1(e[i].to, now);	
		size[now] += size[ e[i].to ];
	}	
}

void dfs2(int now){
	if(size[now] == 1)
		return ;
	if(zf[now]){
		for(int i = ehead[now]; i; i = e[i].next){
			dfs2(e[i].to);
			val[now] = Max(val[now], val[ e[i].to ]);			
		}	
		return ;
	}
	val[now] = 1 << 30;
		for(int i = ehead[now]; i; i = e[i].next){
			dfs2(e[i].to);
			val[now] = Min(val[now], val[ e[i].to ]);			
		}	
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &zf[i]);	
	}
	for(int i = 1, v; i < n; i++){
		scanf("%d", &v);
		add_edge(v, i + 1);	
	}
	dfs1(1, 0);
	for(int i = 1; i <= n; i++){
		if(size[i] == 1){
			a[ ++cnt ] = (node){i, qz[i]};	
		}	
	}
	std::sort(a + 1, a+ cnt + 1, cmp);
	for(int i = 1; i <= cnt; i++)
		val[ a[i].id ] = i;
	dfs2(1);
	printf("%d", val[1]);
}
