#include <cstdio>

const int N = 3e5 + 1e4;

int n, m, op, x, y;

// Splay Start 
struct Splay_node{
    int fa, now, xor_sum;
    bool lazy;
    int son[2];
}tree[N];

int st[N], stcnt;

inline bool get_son(int now){return now == tree[ tree[now].fa ].son[1];}

inline bool not_root(int now){
    return tree[ tree[now].fa ].son[0] == now || tree[ tree[now].fa ].son[1] == now;
}

inline void pushdown(int now){
    if(tree[now].lazy){
        int tmp = tree[now].son[0]; tree[now].son[0] = tree[now].son[1]; tree[now].son[1] = tmp;
        tree[now].lazy = 0;
        tree[ tree[now].son[0] ].lazy ^= 1;
        tree[ tree[now].son[1] ].lazy ^= 1;
    }
}

inline void pushup(int now){
//    pushdown( tree[now].son[0] ); pushdown( tree[now].son[1] );
    tree[now].xor_sum = tree[ tree[now].son[0] ].xor_sum ^ tree[ tree[now].son[1] ].xor_sum ^ tree[now].now;
}

inline void rotate(int now){
    bool kind = get_son(now);	
    int tmp_node = tree[now].fa;
    if( not_root( tree[now].fa ) ) 
        tree[ tree[ tree[now].fa ].fa ].son[ get_son(tree[now].fa) ] = now;
    if(tree[now].son[kind ^ 1]) 
        tree[ tree[now].son[kind ^ 1] ].fa = tmp_node;
    tree[tmp_node].son[kind] = tree[now].son[kind ^ 1]; tree[now].son[kind ^ 1] = tmp_node;
    tree[now].fa = tree[tmp_node].fa; tree[tmp_node].fa = now;
    pushup(now);
    pushup(tmp_node);
}

inline void splay(int now){
    int tmp_y = now; stcnt = 0;
    st[ ++stcnt ] = now;
    while( not_root(tmp_y) ) 
        st[ ++stcnt ] = tmp_y = tree[tmp_y].fa;
    while(stcnt)
        pushdown(st[ stcnt-- ]);
    while( not_root(now) ){
        tmp_y = tree[now].fa;// int tmp_z = tree[tmp_y].fa;
        if(not_root(tmp_y))
            rotate(get_son(tmp_y) ^ get_son(now)? now: tmp_y);		
        rotate(now);
    }
    pushup(now);
}

void access(int now){
    for(int y = 0; now; now = tree[y = now].fa)
        splay(now), tree[now].son[1] = y, pushup(now);
}

inline void makeroot(int now){
    access(now), splay(now);
    tree[now].lazy ^= 1;
	pushdown(now);
} 

inline int findroot(int now){
    access(now); splay(now);
    pushdown(now);
    while(tree[now].son[0]) 
        pushdown( now = tree[now].son[0] );
    splay(now);
    return now;
}

inline void split(int from, int to){
    makeroot(from);
    access(to); splay(to);
}

inline void link(int from,int to){
    makeroot(from);	
    if(findroot(to) != from) tree[from].fa = to;
}

inline void cut(int from,int to){
    makeroot(from);
    if( (findroot(to) == from) && (tree[to].fa = from) && tree[to].son[0] == from  &&(!tree[to].son[0])){
        tree[from].fa = tree[to].son[0] = 0;	
        pushup(to);
    }
}
// Splay End

int main(){
#ifdef woshiluo
    freopen("luogu.3690.in", "r", stdin);
    freopen("luogu.3690.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", &tree[i].now);
    while(m--){
        scanf("%d%d%d", &op, &x, &y);
        if(op == 0){
            split(x, y);
            printf("%d\n", tree[y].xor_sum);
        }
        else if(op == 1) 
            link(x, y);
        else if(op == 2)
            cut(x, y);
        else if(op == 3){
            splay(x);
            tree[x].now = y;
        }
    }
}
