#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N=11000;
const int M=110000;

int n,m,s,t,u,v,w;

// edge start
struct edge{
    int next,to,val,un;
}e[M<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val,int un){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].val=val;
    e[ecnt].next=ehead[now];
    e[ecnt].un=ecnt+un;
    ehead[now]=ecnt;
}
// edge end

namespace Dinic{
    int depth[N],rnow[N];
    int q[N],head,tail;
    inline bool bfs(){
        memset(depth,0,sizeof(depth));
        head=tail=0;
        q[head]=s;
        depth[s]=1;
        while(head<=tail){
            for(int i=ehead[q[head]];i;i=e[i].next){
                if(e[i].val>0&&depth[e[i].to]==0){
                    q[++tail]=e[i].to;
                    depth[e[i].to]=depth[q[head]]+1;
                }
            }
            head++;
        }
        if(depth[t]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==t) return dist;
        int fl=0,di;
        for(int& i=rnow[now];i;i=e[i].next){
            if(depth[e[i].to]==depth[now]+1&&e[i].val!=0){
                di=dfs(e[i].to,Min(dist,e[i].val));
                if(di>0){
                    e[i].val-=di;
                    e[e[i].un].val+=di;
                    fl+=di;
                    dist-=di;
#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int N=11000;
const int M=110000;

int n,m,s,t,u,v,w;

// edge start
struct edge{
    int next,to,val,un;
}e[M<<1];
int ehead[N],ecnt;
inline void add_edge(int now,int to,int val,int un){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].val=val;
    e[ecnt].next=ehead[now];
    e[ecnt].un=ecnt+un;
    ehead[now]=ecnt;
}
// edge end

namespace Dinic{
    int depth[N],rnow[N];
    int q[N],head,tail;
    inline bool bfs(){
        memset(depth,0,sizeof(depth));
        head=tail=0;
        q[head]=s;
        depth[s]=1;
        while(head<=tail){
            for(int i=ehead[q[head]];i;i=e[i].next){
                if(e[i].val>0&&depth[e[i].to]==0){
                    q[++tail]=e[i].to;
                    depth[e[i].to]=depth[q[head]]+1;
                }
            }
            head++;
        }
        if(depth[t]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==t) return dist;
        int fl=0,di;
        for(int& i=rnow[now];i;i=e[i].next){
            if(depth[e[i].to]==depth[now]+1&&e[i].val!=0){
                di=dfs(e[i].to,Min(dist,e[i].val));
                if(di>0){
                    e[i].val-=di;
                    e[e[i].un].val+=di;
                    fl+=di;
                    dist-=di;
                    if(!dist) break;
                }
            }
        }
        return fl;
    }
    inline int dinic(){
        int ans=0;
        while(bfs()){
            for(int i=1;i<=n;i++) rnow[i]=ehead[i];
            while(int d=dfs(s,0x7fffffff)) ans+=d;
        }
        return ans;
    }
}


int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w,1);
        add_edge(v,u,0,-1);
    }
    printf("%d",Dinic::dinic());
}
