#include <cstdio>

inline int Min(int a, int b){return a < b? a: b;}

const int N = 11000;
const int M = 51000;

int n, m, u, v;

// edge start 
struct edge{
    int to, next;
}e[M], ne[M];
int ehead[N], ecnt, nehead[N], necnt;
inline void add_edge(int now, int to, int ehead[], int &ecnt, edge e[]) {
    ecnt++;
    e[ecnt].to = to;
    e[ecnt].next = ehead[now];
    ehead[now] = ecnt;
}
// edge end

// tarjan start
int dfn[N], low[N], cnt[N], size[N], st[N], col[N], scnt, col_cnt, time;
bool vis[N];
void tarjan(int now){
    vis[now] = true;
    dfn[now] = low[now] = ++time;	
    st[ ++scnt ] = now;
    for(int i = ehead[now]; i; i = e[i].next){
        if(!dfn[ e[i].to ]){
            tarjan( e[i].to );
            low[now] = Min(low[now], low[ e[i].to ]);
        }
        else if(vis[ e[i].to ])
            low[now] = Min(low[now], dfn[ e[i].to ]);
    }
    if(low[now] == dfn[now]){
        col[now] = ++col_cnt;
        vis[now] = 0;
        cnt[col_cnt] = 1;
        while(st[ scnt ] != now){
            col[ st[scnt] ] = col_cnt;
            vis[ st[scnt] ] = false;
            cnt[col_cnt]++;
            scnt--;
        }
        scnt--;
    }
}

inline void tarjan_run(){
    for(int i = 1; i <= n; i++){
        if(!dfn[i])
            tarjan(i);		
    }		
}
// tarjan end

inline bool check(int now, int to){
    for(int i = nehead[now]; i; i = ne[i].next){
        if(ne[i].to == to) return true;
    }
    return false;
}

inline void build_new_grapg(){
    for(int u = 1; u <= n; u++){
        for(int i = ehead[u]; i; i = e[i].next){
            if(check(col[ e[i].to ], col[u]) || col[u] == col[ e[i].to ] )  continue;
            add_edge(col[ e[i].to ], col[u], nehead, necnt, ne);
        }
    }	
}

void dfs(int now){
    size[now] = cnt[now];
    for(int i = nehead[now]; i; i = ne[i].next){
        dfs(ne[i].to);
        size[now] += size[ ne[i].to ];
    }	
}

inline void get_ans(){
    for(int i = 1; i <= col_cnt; i++){
        if(size[i] == 0) 
            dfs(i);
    }
}

int main(){
#ifdef woshiluo
    freopen("luogu.2341.in", "r", stdin);
    freopen("luogu.2341.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);	
    for(int i = 1; i <= m; i++){
        scanf("%d%d", &u, &v);
        add_edge(u, v, ehead, ecnt, e);
    }

    tarjan_run();
    build_new_grapg();

    get_ans();
    for(int i = 1; i <= col_cnt; i++){
        if(size[i] >= n){
            printf("%d\n", cnt[i]);
            return 0;
        }
    }
    printf("0\n");
}
