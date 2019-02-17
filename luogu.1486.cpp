#include <cstdio>

const int N = 110000;

int n, x, Min_wage, cnt, gugu_cnt;
char op[3];

struct Splay_node{
	int val, cnt, size;
	Splay_node *son[2], *fa;	
}pre_splay[N], *root;

int pre_splay_cnt;

inline bool get_son(Splay_node *now) {return now -> fa == 0 ? 0: (now -> fa -> son[1] == now);}
inline int get_size(Splay_node *now) {return now == 0 ? 0: now -> size;}

inline void pushup(Splay_node *now) {now -> size = get_size(now -> son[0]) + get_size(now -> son[1]) + now -> cnt;}

inline void rotate(Splay_node *now){
	bool kind = get_son(now);	
	Splay_node *tmp1 = now -> fa;
	if( now -> fa -> fa== 0 )  now -> fa = 0, root = now;
	else now -> fa -> fa -> son[ get_son(now -> fa) ] = now; now -> fa = tmp1 -> fa;
	tmp1 -> son[kind] = now -> son[ kind ^ 1 ]; if(tmp1 -> son[kind]) tmp1 -> son[kind] -> fa = tmp1;
	now -> son[ kind ^ 1 ] = tmp1; tmp1 -> fa = now;
	pushup(tmp1); pushup(now);
}

inline void splay(Splay_node *from, Splay_node *to){
	Splay_node *tmp1, *tmp2;
	while(from -> fa != to){
		tmp1 = from -> fa; tmp2 = tmp1 -> fa;
		if(tmp2 == to) rotate(from);
		else {
			if( get_son(from) != get_son(tmp1) ) rotate(tmp1), rotate(from);
			else rotate(from), rotate(from);
		}
	}
}

inline void del_pre(int val){
	Splay_node *now = root, *tmp;
	while(now){
		if( now -> val < val && ( tmp == 0 ||  now -> val > tmp -> val ) ) tmp = now;
		now = now -> son[now -> val < val];
	}
	tmp -> fa -> son[ get_son(tmp) ] = 0;
	gugu_cnt += tmp -> size;
	tmp = tmp -> fa;
	while(tmp){ pushup(tmp); tmp = tmp -> fa; }
}

inline void insert(int val){
	if( val < Min_wage ) return ;
	val += -1 * cnt;
	Splay_node *now = root, *tmp1;
	while(now){
		if( now -> val == val ) { now -> cnt ++; tmp1 = now; break; }
		else if( now -> val < val ){
			if( now -> son[1] ) now = now -> son[1];
			else {
				now -> son[1] = &pre_splay[ ++pre_splay_cnt ];	
				*(now -> son[1]) = (Splay_node){val, 1, 1, {0, 0}, now};
				tmp1 = now -> son[1];
				break;
			}
		}
		else if(now -> val > val){
			if( now -> son[0] ) now = now -> son[0];
			else {
				now -> son[0] = &pre_splay[ ++pre_splay_cnt ];	
				*(now -> son[0]) = (Splay_node){val, 1, 1, {0, 0}, now};
				tmp1 = now -> son[0];
				break;
			}
		}
	}
	while(now) { pushup(now); now = now -> fa; }
	splay(tmp1, 0);
}

inline void add_all(int val) {cnt += val;}
inline void less_all(int val){
	cnt -= val;
	if( cnt < 0 ) del_pre(-val);
}

inline int get_rank_x(int val){
	Splay_node *now = root;
	while(now){
		if(now -> cnt + get_size(now -> son[0]) > val) val -= now -> cnt + get_size(now -> son[0]), now = now -> son[1] ;
		else if( get_size(now -> son[0]) > val ) return now -> val; 
		else now = now -> son[1];
	}
	return 0;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("luogu.1486.in", "r", stdin);
	freopen("luogu.1486.out", "w", stdout);
#endif
	root = &pre_splay[0];
	scanf("%d%d", &n, &Min_wage);	
	for(int i = 1; i <= n; i++){
		scanf("%s%d", op, &x);
		if(op[0] == 'I') insert(x);
		else if(op[0] == 'A') add_all(x);
		else if(op[0] == 'S') less_all(x);	
		else if(op[0] == 'x') printf("%d", get_rank_x(x));
	}
	printf("%d", gugu_cnt);
}
