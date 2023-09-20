#include <cstdio>

const int N = 110000;

int op, n, m, x, y;
double k, z, tmp_double;

struct node{
	double sum, square; 
	void operator+=(const node &b){
		this -> sum += b.sum;
		this -> square += b.square;
	}
}tmp;

node tree[N << 2];
double lazy[N << 2];
inline void pushup(int now){
	tree[now].sum = tree[now << 1].sum + tree[now << 1 | 1].sum;
	tree[now].square = tree[now << 1].square + tree[now << 1 | 1].square;
}
inline void pushdown(int now, int lson, int rson){
	if(lazy[now]){
		tree[now << 1].square  = tree[now << 1].square + (lazy[now] * tree[now << 1].sum * 2.0) + (lazy[now] * lazy[now]) * lson;
		tree[now << 1].sum += lazy[now] * lson;	
		tree[now << 1 | 1].square  = tree[now << 1 | 1].square + (lazy[now] * tree[now << 1 | 1].sum * 2.0) + (lazy[now] * lazy[now]) * rson;
		tree[now << 1 | 1].sum += lazy[now] * rson;	
		lazy[now << 1] += lazy[now];
		lazy[now << 1 | 1] += lazy[now];
		lazy[now] = 0;
	}
}
inline void query_add(int now, int left, int rig, int from, int to, double val){
	if(from <= left && rig <= to){
		tree[now].square = tree[now].square + ((val * tree[now].sum ) * 2) + (val * val) * (rig - left + 1);
		tree[now].sum = tree[now].sum + val * (rig - left + 1);
		lazy[now] += val; 
		return ;
	}	
	int mid = (left + rig) >> 1;
	pushdown(now, mid - left + 1, rig - mid);
	if(from <= mid) query_add(now << 1, left, mid, from, to, val);
	if(to > mid) query_add(now << 1 | 1, mid + 1, rig, from, to, val);
	pushup(now);
}
inline node query_sum(int now, int left, int rig, int from, int to){
	if(from <= left && rig <= to){
		return tree[now];
	} 
	int mid = (left + rig) >> 1; node res = (node){0, 0};
	pushdown(now, mid - left + 1, rig - mid);
	if(from <= mid) res += query_sum(now << 1, left, mid, from, to);
	if(to > mid) res += query_sum(now << 1 | 1, mid + 1, rig, from, to);
	return res;
}

int main(){
#ifdef woshiluo
	freopen("luogu.1471.in", "r", stdin);
	freopen("luogu.1471.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%lf", &z);
		query_add(1, 1, n, i, i, z);
	}
	while(m--){
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d%lf", &x, &y, &z);
			k += (y - x + 1) * z;
			query_add(1, 1, n, x, y, z);
		}
		else if(op == 2){
			scanf("%d%d", &x, &y);
			tmp = query_sum(1, 1, n, x, y);
			printf("%.4lf\n", tmp.sum / (y - x + 1));
		}
		else if(op == 3){
			scanf("%d%d", &x, &y);
			tmp = query_sum(1, 1, n, x, y);
			printf("%.4lf\n", ( (tmp.square + (tmp.sum / (y - x + 1)) * tmp.sum - ( 2 * tmp.sum * (tmp.sum / (y - x + 1)) ) ) / (y - x + 1) ) );
		}
	}
}
