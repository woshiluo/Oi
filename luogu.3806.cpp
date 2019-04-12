#include <cstdio>
#include <algorithm>

inline int Max(int a, int b) {return a > b? a: b;}

const int N = 11000;
const int M = 110;

int n, m; 
// edge start
struct edge{
	int next, val, to;
}e[N << 1];
int ecnt, ehead[N];
inline void add_edge(int now, int to, int val){
	ecnt++;
	e[ecnt].to = to;
	e[ecnt].val = val;
	e[ecnt].next = ehead[now];
	ehead[now] = ecnt;
}
// edge end
int query[M];

int rt, SIZE, dcnt;
bool use[N];
int f[N], size[N], dis[N], ans[N];

int binary_search(int left, int now){
	int res = 0, rig = dcnt;
	while(left <= rig){
		int mid = (left + rig) >> 1;	
		if(dis[mid] <= now) res = mid, left = mid + 1;
		else rig = mid - 1;
	}
	return res;
}

int binary_search2(int left, int now){
	int res = 0, rig = dcnt;
	while(left <= rig){
		int mid = (left + rig) >> 1;	
		if(dis[mid] < now) left = mid + 1;
		else res = mid, rig = mid - 1;
	}
	return res;
}

void get_root(int now, int fa){
	f[now] = 0; size[now] = 1;	
	for(int i = ehead[now]; i; i = e[i].next){
		if( use[ e[i].to ] || e[i].to == fa )
			continue;
		get_root(e[i].to, now);
		f[now] = Max(f[now], size[ e[i].to ]);
		size[now] += size[ e[i].to ];
	}
	f[now] = Max(f[now], SIZE - size[now]);
	if(f[now] < f[rt]) rt = now;
}

void get_dis(int now, int fa, int d){
	for(int i = ehead[now]; i; i = e[i].next){
		if( use[e[i].to] || e[i].to == fa )
			continue;
		dis[ ++dcnt ] = d + e[i].val;
		get_dis(e[i].to, now, dis[dcnt]);
	}
}

void get_ans(int now, int add, int D){
	dis[dcnt = 1] = D;
	get_dis(now, 0, D);
	std::sort(dis + 1, dis + dcnt + 1);
	for(int i = 1; i <= m; i++){
		int p = 1, k = query[i];
		while(p < dcnt && dis[p] + dis[dcnt] < k) 
			p ++;
		while(p < dcnt && k - dis[p] >= dis[p]){
			int left = binary_search2(p + 1, k - dis[p]), rig = binary_search(p + 1, k - dis[p]);
			if(rig >= left)
				ans[i] += (rig - left + 1) * add;
			p ++;
		}
	}
}

void dfs(int now){
	use[now] = true; get_ans(now, 1, 0);
	for(int i = ehead[now]; i; i = e[i].next){
		if(use[ e[i].to ])
			continue;
		get_ans(e[i].to, -1, e[i].val);
		SIZE = size[ e[i].to ], rt = 0;
		get_root(e[i].to, now); 
		dfs(rt);
	}
}

int main(){
#ifdef woshiluo
	freopen("luogu.3806.in", "r", stdin);
	freopen("luogu.3806.out", "w" , stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1, u, v, w; i < n; i++){
		scanf("%d%d%d", &u, &v ,&w);	
		add_edge(u, v, w);
		add_edge(v, u, w);
	}
	for(int i = 1; i <= m; i++) scanf("%d", &query[i]);

	SIZE = n; f[0] = 0x3f3f3f3f;
	get_root(1, 0);
	dfs(rt);

	for(int i = 1; i <= m; i++)
		printf("%s\n", ans[i]? "AYE": "NAY");
}
