#include <cstdio>

const int N = 4e5 + 1e4;
const long long mod = 1e9 + 7;

int n, q, x, y, z, pcnt;
int a[N];
long long p[310], pri[N], inv[310];
char op[10];

inline long long ksm(long long a, long long p){
	long long res = 1;
	while(p){
		if(p & 1) res = (res * a) % mod;
		a = (a * a) % mod;
		p >>= 1;
	}
	return res;
}

inline void prime(){
	for(int i = 2; i <= 300; i++){
		for(int j = 1; j <= pcnt; j++)
			if(i % p[j] == 0) pri[i] |= pri[ p[j] ];
		if(pri[i] == 0) {p[++pcnt] = i; pri[i] = (1LL << (pcnt - 1LL));}
	}
}

inline void get_inv(){
	for(int i = 1; i <= pcnt; i++) 
		inv[i] = ksm(p[i], mod - 2);
}

// Segment Tree Start
struct node{
	long long val,pri;
	void operator+= (const node &b){
		this -> val = (this -> val * b.val) % mod;
		pri |= b.pri;
	}
}tree[N << 2], lazy[N << 2];

inline void pushup(int now){
	tree[now].val = (tree[now << 1].val * tree[now << 1 | 1].val) % mod;
	tree[now].pri = tree[now << 1].pri | tree[now << 1 | 1].pri;
}

inline void pushdown(int now, int lson, int rson){
	if(lazy[now].pri != 0){
		tree[now << 1].val  =  (1LL * tree[now << 1].val * ksm(lazy[now].val, lson)) % mod;
		tree[now << 1 | 1].val  =  (1LL * tree[now << 1 | 1].val * ksm(lazy[now].val, rson)) % mod;
		tree[now << 1].pri |= lazy[now].pri;
		tree[now << 1 | 1].pri |= lazy[now].pri;
		lazy[now << 1].val = (1LL * lazy[now << 1].val * lazy[now].val) % mod;
		lazy[now << 1 | 1].val = (1LL * lazy[now << 1 | 1].val * lazy[now].val) % mod;
		lazy[now << 1].pri |= lazy[now].pri;
		lazy[now << 1 | 1].pri |= lazy[now].pri;
		lazy[now].val = 1LL; lazy[now].pri = 0;
	}
}


inline void query_mut(int now, int left, int rig, int from, int to, int val){
	if(from <= left && rig <= to){
		tree[now].val = (1LL * tree[now].val * ksm(val, (rig - left + 1LL))) % mod;
		tree[now].pri |= pri[val]; 
		lazy[now].val = (lazy[now].val * val) % mod;
		lazy[now].pri |= pri[val];
		return ;
	}
	int mid = (left + rig) >> 1;
	pushdown(now, mid - left + 1LL, rig - mid);
	if(from <= mid) query_mut(now << 1, left, mid, from, to, val);
	if(to > mid) query_mut(now << 1 | 1, mid + 1, rig, from, to, val);
	pushup(now);
}

inline node query_sum(int now, int left, int rig, int from, int to){
	if(from <= left && rig <= to) return tree[now];
	int mid = (left + rig) >> 1;
	node res = (node){1, 0};
	pushdown(now, mid - left + 1LL, rig - mid);
	if(from <= mid) res += query_sum(now << 1, left, mid, from, to);
	if(to > mid) res += query_sum(now << 1 | 1, mid + 1, rig, from, to);	
	pushup(now);
	return res;
}

inline void build_tree(int now, int left, int rig){
	lazy[now].val = 1; lazy[now].pri = 0;
	if(left == rig){
		scanf("%lld", &tree[now].val);
		tree[now].pri = pri[ tree[now].val ];
		return ;
	}
	int mid = (left + rig) >> 1;
	build_tree(now << 1, left, mid);
	build_tree(now << 1 | 1, mid + 1, rig);
	pushup(now);
}
// Segment Tree End

int main(){
	prime();
	get_inv();
	scanf("%d%d", &n, &q);
	build_tree(1, 1, n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);	
	while(q--){
		scanf("%s", op);	
		if(op[0] == 'M'){
			scanf("%d%d%d", &x, &y, &z);	
			query_mut(1, 1, n, x, y, z);
		}	
		else {
			scanf("%d%d", &x, &y);
			node tmp = query_sum(1, 1, n, x, y);
			for(int i = 1; i <= pcnt; i++){
				if((tmp.pri >> (i - 1LL)) & 1LL)
					tmp.val = (((tmp.val * (p[i] - 1) ) % mod) * inv[i]) % mod;
			}
			printf("%lld\n", tmp.val);
		}
	}	
}
