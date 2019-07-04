#include <cstdio>

const int N = 110000; 

int n, x, tree_cnt, ans, min, root;
char op[3];

struct node{
	int val, cnt, lazy, size;
	int son[2], fa;
}tree[N];

inline bool get_son(int now){return tree[ tree[now].fa ].son[1] == now;}

inline void pushup(int now){
	tree[now].size = tree[ tree[now].son[0] ].size + tree[ tree[now].son[1] ].size + tree[now].cnt;
}

inline void pushdown(int now){
	if(tree[now].lazy){
		if(tree[now].son[0])
			tree[ tree[now].son[0] ].val += tree[now].lazy,tree[ tree[now].son[0] ].lazy += tree[now].lazy;
		if(tree[now].son[1])
			tree[ tree[now].son[1] ].val += tree[now].lazy, tree[ tree[now].son[1] ].lazy += tree[now].lazy;
		tree[now].lazy = 0;
	}
}

void rotate(int now){
	int tmp = tree[now].fa; bool kind = get_son(now);
	if(tmp == 0)
		return ;
	if(tree[tmp].fa == 0) 
		root = now;	
	pushdown(tmp); pushdown(now);
	if(tree[tmp].fa) tree[ tree[tmp].fa ].son[ get_son(tmp) ] = now;
	tree[now].fa = tree[tmp].fa; 
	tree[tmp].son[kind] = tree[now].son[kind ^ 1]; if(tree[now].son[kind ^ 1]) tree[ tree[now].son[kind ^ 1] ].fa = tmp;
	tree[now].son[kind ^ 1] = tmp; tree[tmp].fa = now;
	pushup(tmp); pushup(now);
}

void splay(int from, int to = 0){
	if(from == to)
		return ;
	while(tree[from].fa != to){
		int tmp_fa = tree[from].fa, tmp_fa2 = tree[ tree[from].fa ].fa;
		if(tmp_fa2 != to)
			rotate(get_son(from) == get_son(tmp_fa)? tmp_fa: from);	
		rotate(from);
	}
}

void insert(int val){
	if(root == 0){
		tree[ ++tree_cnt ] = (node){val, 1, 0, 1, {0, 0}, 0};
		root = tree_cnt;
		return ;
	}
	int now = root;	

	while(now){
		pushdown(now);
		if(tree[now].val == val){ tree[now].cnt ++; break; }

		if(tree[now].val > val){
			tree[now].size++;
			if(tree[now].son[0])
				now = tree[now].son[0];
			else {
				tree[ ++tree_cnt ] = (node){val, 1, 0, 1, {0, 0}, now}; 
				tree[now].son[0] = tree_cnt;
				now = tree[now].son[0];
				break;
			}
		}
		else {
			tree[now].size++;
			if(tree[now].son[1])
				now = tree[now].son[1];
			else {
				tree[ ++tree_cnt ] = (node){val, 1, 0, 1, {0, 0}, now};
				tree[now].son[1] = tree_cnt;
				now = tree[now].son[1];
				break;
			}
		}
	}

	splay(now);
}

int lower(int val){
	int now = root, res = 0; tree[0].val = -0x7fffffff;
	while(now){
		pushdown(now);
		if(tree[now].val < val && tree[now].val > tree[res].val) res = now;
		if(val > tree[now].val) now = tree[now].son[1];
		else now = tree[now].son[0];
	}
	if(res) splay(res);
	return res;
}

int find(int val){	
	if(val > tree[root].size)
		return -1;
	int now = root;
	while(now){
		pushdown(now);
		if(tree[ tree[now].son[1] ].size + tree[now].cnt < val) val -= tree[ tree[now].son[1] ].size + tree[now].cnt, now = tree[now].son[0];
		else if(tree[ tree[now].son[1] ].size < val) break;
		else now = tree[now].son[1];
	}
	splay(now);	
	return tree[now].val;
}

inline void add(int val){
	tree[root].lazy += val;
	tree[root].val += val;
}

inline void sub(int val){
	tree[root].lazy -= val;
	tree[root].val -= val;
	int tmp = lower(min);
	if(tmp){
		splay(tmp);
		ans += tree[ tree[tmp].son[0] ].size + tree[tmp].cnt;	
		root = tree[tmp].son[1];
		tree[root].fa = 0;
		pushup(root);
	}
}

int main(){
#ifdef woshiluo 
	freopen("luogu.1486.in", "r", stdin);
	freopen("luogu.1486.out", "w", stdout);
#endif
	scanf("%d%d", &n, &min);
	while(n--){
		scanf("%s%d", op, &x);
		if(op[0] == 'I' && x >= min)
			insert(x);
		else if(op[0] == 'A')
			add(x);
		else if(op[0] == 'S')
			sub(x);
		else if(op[0] == 'F')
			printf("%d\n", find(x));
	}
	printf("%d", ans);
}
