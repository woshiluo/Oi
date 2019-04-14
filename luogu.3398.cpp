#include <cstdio>

const int N = 110000; 

int n, q;

// Segment Start
int tree[N << 2], lazy[N << 2];
inline void pushup(int now){tree[now] = Min(tree[now << 1], tree[now << 1|1]);}

inline void pushdown(int now){
	if(lazy[now]){
		tree[now << 1] = lazy[now];
		tree[now << 1|1] = lazy[now];
		lazy[now << 1] = lazy[now];
		lazy[now << 1|1] = lazy[now];
		lazy[now] = 0;
	}
}

void query_set(int now, int left, int rig, int from, int to, int val){
	if(from <= left && rig <= to){
		tree[now] = lazy[now] = val;	
		return ;
	}
	pushdown(now);
	int mid = (left + rig) >> 1;
	if(from <= mid) query_set(now << 1, left, mid, from, to, val);
	if(to > mid) query_set(now << 1|1, mid + 1, rig, from, to, val);
	pushup(now);
	return ;
}

int query_min(int now, int left, int rig, int from, int to){
	if(from <= left && rig <= to)
		return tree[now]; 
	pushdown(now);
	int mid = (left + rig) >> 1, res = 0;
	if(from <= mid) res = query_max(now << 1, left, mid, from, to);
	if(to > mid) res = Min(query_max(now << 1|1, mid + 1, rig, from, to), res);
	return res;
	
}
// Segment End

int main(){
	scanf("%d%d", &n, &q);
	for(int i = 1, u, v; i < n; i++){
		scanf("%d%d", &u, &v);	
		add_edge(u, v);
		add_edge(v, u);
	}
	while(q--){
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		
	}
}
