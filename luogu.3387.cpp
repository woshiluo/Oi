#include <cstdio>
#include <cstring>

inline int Min(int a, int b) { return a < b? a: b; }
inline int Max(int a, int b) { return a > b? a: b; }

const int N = 1e4 + 1e3;
const int M = 1e5 + 1e4;

int n, m, ans;
int _val[N], val[N], from[M], to[M];

// Edge Start 
struct edge {
    int next, to;
} e[M];
int ehead[N], ecnt;

void edge_init() {
    ecnt = 0;
    memset(ehead, 0, sizeof(ehead));
}

inline void add_edge(int now, int to) {
    ecnt ++;
    e[ecnt].to = to;
    e[ecnt].next = ehead[now];
    ehead[now] = ecnt;
}
// Edge End

// Tarjan Start
int dfn[N], low[N], time_index;
int col[N], col_cnt;
int st[N], stcnt;
bool vis[N];
void tarjan(int now){
    vis[now] = true;
    st[ ++ stcnt ] = now;
    dfn[now] = low[now] = ++ time_index;
    for(int i = ehead[now]; i; i = e[i].next) {
        if( dfn[ e[i].to ] == 0 ){
            tarjan( e[i].to );
            low[now] = Min(low[now], low[ e[i].to ]);
        }
        else if( vis[ e[i].to ] )
            low[now] = Min(low[now], dfn[ e[i].to ]); 
    }
    if( dfn[now] == low[now] ) {
        ++ col_cnt;
        while( st[ stcnt + 1 ] != now ) {
            int tmp = st[ stcnt -- ];
            col[tmp] = col_cnt;
            val[col_cnt] += _val[tmp];
            vis[tmp] = false;
        }
    }
}

void _tarjan() {
    for(int i = 1; i <= n; i++){
        if( dfn[i] == 0 )
            tarjan(i);
    }
}
// Tarjan End

void build_new_graph(){
    edge_init();
    for(int i = 1; i <= m; i++) {
        if( col[ from[i] ] != col[ to[i] ] )
            add_edge(col[ from[i] ], col[ to[i] ]);
    }
} 

int f[N];

void dfs(int now){
    if(vis[now])
        return ;
    vis[now] = true;
    f[now] = val[now];
    for(int i = ehead[now]; i; i = e[i].next){
        dfs(e[i].to);
        f[now] = Max(f[now], val[now] + f[ e[i].to ]);
    }
}

int main() {
#ifdef woshiluo
    freopen("luogu.3387.in", "r", stdin);
    freopen("luogu.3387.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) 
        scanf("%d", &_val[i]);
    
    for(int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        from[i] = u, to[i] = v;
        add_edge(u, v);
    }

    _tarjan();
    
    build_new_graph();

    for(int i = 1; i <= col_cnt; i++) {
        if( vis[i] == false )
            dfs(i);
        ans = Max(ans, f[i]);
    }
    
    printf("%d", ans);
}
