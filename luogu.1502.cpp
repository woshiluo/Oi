#include <cstdio>
#include <algorithm>

const int N = 11000;

int _case, Max_ans, xcnt;
int n, W, H;
int left[N], rig[N];

struct node{
	int now, light, id;
	bool fl;
}x[N << 1], y[N << 1];

bool cmp(node a, node b) {return a.now < b.now;}

bool cmp1(node a, node b) {return a.now == b.now ? a.light > b.light: a.now < b.now;}

inline int Max(int a, int b) {return a > b? a : b;}

inline void init(){ Max_ans = xcnt = 0; }

inline void readin(){
	scanf("%d%d%d", &n, &W, &H);
	for(int i = 1; i <= n; i++){
		scanf("%d%d%d", &x[i].now, &y[i].now, &x[i].light);	
		y[i].id = x[i].id = i;
		x[i].fl = y[i].fl = false;
		y[i].light = x[i].light;
	}
}

inline void get_pre(){
	for(int i = 1; i <= n; i++){
		x[i + n] = x[i];
		y[i + n] = y[i];
		x[i + n].now += W - 1;
		x[i + n].fl = true;		
		y[i + n].now += H - 1;
		y[i + n].light = -y[i].light;
	}
	std::sort(x + 1, x + (n << 1) + 1, cmp);
	for(int i = 1; i <= (n << 1); i++){
		if(i == 1 || x[i].now != x[i - 1].now) xcnt++;	
		if(!x[i].fl) left[ x[i].id ] = xcnt;
		else rig[ x[i].id ] = xcnt; 
	}
	std::sort(y + 1, y + (n << 1) + 1, cmp1);
}
// Segment Tree Start
int tree[N << 3], lazy[N << 3];

inline void pushup(int now){tree[now] = Max(tree[now << 1], tree[now << 1 | 1]);}

inline void pushdown(int now){
	if(lazy[now]){
		tree[now << 1] += lazy[now];
		tree[now << 1 | 1] += lazy[now];
		lazy[now << 1] += lazy[now];
		lazy[now << 1 | 1] += lazy[now];
		lazy[now] = 0 ;
	}
}

void build_tree(int now, int left, int rig){
	if(left == rig){
		tree[now] = lazy[now] = 0;
		return ;
	}
	int mid = (left + rig) >> 1;
	build_tree(now << 1, left, mid);
	build_tree(now << 1 | 1, mid + 1, rig);
	tree[now] = lazy[now] = 0;
}

int query_Max(int now, int left, int rig, int from, int to){
	if(from <= left && rig <= to){ return tree[now]; }
	pushdown(now);
	int mid = (left + rig) >> 1, res = 0;
	if(from <= mid) res = Max(query_Max(now << 1, left, mid, from, to), res);
	if(to > mid) res = Max(query_Max(now << 1 | 1, mid + 1, rig, from, to), res);
	return res;
}

void query_add(int now, int left, int rig, int from, int to, int val){
	if(from <= left && rig <= to){
		tree[now] += val;	
		lazy[now] += val;
		return ;
	}
	pushdown(now);
	int mid = (left + rig) >> 1;
	if(from <= mid) query_add(now << 1, left, mid, from, to, val);
	if(to > mid) query_add(now << 1 | 1, mid + 1, rig, from, to, val);
	pushup(now);
}
// Segment Tree End

void get_ans(){
	build_tree(1, 1, xcnt);
	for(int i = 1, tmp; i <= (n << 1); i++){
		if(y[i].light > 0){
			tmp = query_Max(1, 1, xcnt, left[ y[i].id ], rig[ y[i].id ]);	
			tmp += y[i].light;
			Max_ans = Max(tmp, Max_ans);
		}
		query_add(1, 1, xcnt, left[ y[i].id ], rig[ y[i].id ], y[i].light);
	}	
	printf("%d\n", Max_ans);
}

int main(){
#ifdef woshiluo
	freopen("luogu.1502.in", "r", stdin);
	freopen("luogu.1502.out", "w", stdout);
#endif
	scanf("%d", &_case);
	while(_case--){
		init();	
		readin();
		get_pre();
		get_ans();
	}
}
