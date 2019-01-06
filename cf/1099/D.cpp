#include <cstdio>
#include <cstdlib>

inline int Min(int a,int b){return a<b?a:b;}

const int N=1e5+2e4;
const int INF=2147483640;

int n,v;
long long sum=0;
int s[N],a[N],son[N];

// edge start 
struct edge{
    int to,next;
}e[N<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].next=ehead[now];
    ehead[now]=ecnt;
}
// edge end

void dfs(int now,int val){
    if(s[now]<=-1){
        int tmp=INF;
        for(int i=ehead[now];i;i=e[i].next){
            tmp=Min(s[e[i].to],tmp); 
        }
        if(tmp==INF) return ;
        tmp-=val;a[now]=tmp;
        for(int i=ehead[now];i;i=e[i].next){
            s[e[i].to]-=val+a[now];
        }
        for(int i=ehead[now];i;i=e[i].next){
            dfs(e[i].to,val+a[now]);
        }
        return ;
    }
    a[now]=s[now];
    for(int i=ehead[now];i;i=e[i].next){
        dfs(e[i].to,val+a[now]);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        scanf("%d",&v);
        add_edge(v,i);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&s[i]);
        if(s[i]!=-1&&s[i]<s[1]){
            printf("-1");
            return 0;
        }
    }
    dfs(1,0);
    sum=0;
    for(int i=1;i<=n;i++){
        if(a[i]<0){
            printf("-1");
            return 0;
        }
        sum+=a[i];
    }
    printf("%lld",sum);
}
