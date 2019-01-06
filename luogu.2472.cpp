#include <cstdio>
#include <cstring>

inline int Min(int a,int b){return a<b?a:b;}

const int R=40;
const int INF=0x7fffffff;

int r,c,d,xcnt,pcnt,based,tmp,leftx,lefty,rigx,rigy;
int a[R][R],pil[R*R*R*R];
char tmp_s[R];

// edge start 
struct edge{
    int to,next,val;
}e[R*R*R*R*R];
int ehead[R*R*R*R],ecnt;

inline void add_edge(int now,int to,int val){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].val=val;
    e[ecnt].next=ehead[now];
    ehead[now]=ecnt;
}
// edge end

inline bool cover(int left,int rig){
//    if(left%c==0) leftx=left/c-1,lefty=c;
//    else leftx=left/c,lefty=left%c;
//    if(rig%c==0) rigx=rig/c-1,rigy=c;
//    else rigx=rig/c,rigy=rig%c;
//    return d*d>=(leftx-rigx)*(leftx-rigx)+(lefty-rigy)*(lefty-rigy);
    return d*d>=(left/(c+1)-rig/(c+1))*(left/(c+1)-rig/(c+1))+(left%(c+1)-rig%(c+1))*(left%(c+1)-rig%(c+1));
}

namespace Dinic{
    int start,end,head,tail,res,dd;
    int que[R*R*R],dep[R*R*R],cur[R*R*R];
    inline bool bfs(){
        memset(dep,0,sizeof(dep));      
        head=tail=0;
        dep[start]=1;
        que[head]=start;
        while(head<=tail){
            for(int i=ehead[que[head]];i;i=e[i].next){
                if(e[i].val>0&&dep[e[i].to]==0){
                    dep[e[i].to]=dep[que[head]]+1;
                    que[++tail]=e[i].to;
                }            
            }
            head++;
        }
        if(dep[end]==0) return false;
        else return true;
    }

    int dfs(int now,int dist){
        if(now==end) return dist;
        int fl=0,di;
        for(int& i=cur[now];i;i=e[i].next){
            if(dep[e[i].to]==dep[now]+1&&e[i].val!=0){
                di=dfs(e[i].to,Min(e[i].val,dist));
                if(di>0){
                    e[i].val-=di;
                    e[i+(i&1?-1:+1)].val+=di;
                    dist-=di;
                    if(dist<=0) break; 
                    fl+=di;
                }
            }
        }
        return fl;
    }

    inline int dinic(){
        res=0;dd=1;
        while(bfs()){
            for(int i=1;i<=(based<<1)+10;i++) cur[i]=ehead[i];
            while(1){
                dd=dfs(start,INF);
                if(dd==0) break;
                res+=dd;
            }
        }
        return res;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("luogu.2472.in","r",stdin);
    freopen("luogu.2472.out","w",stdout);
#endif
    scanf("%d%d%d",&r,&c,&d);
    based=r*(c+1)+10;
    Dinic::start=(based<<1)+3;
    Dinic::end=(based<<1)+4;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            scanf("%1d",&a[i][j]);             
            if(a[i][j]!=0){
                tmp=(i-1)*(c+1)+j;
                pil[++pcnt]=tmp; 
                add_edge(tmp,based+tmp,a[i][j]);
                add_edge(based+tmp,tmp,0);
                if(i+d>r||i-d<1||j+d>c||j-d<1) {
                    add_edge(based+tmp,Dinic::end,INF);
                    add_edge(Dinic::end,based+tmp,0);
                }
            }
        } 
    }

    for(int i=1;i<=pcnt;i++){
        for(int j=1;j<=pcnt;j++){
            if(cover(pil[i],pil[j])&&i!=j){
                add_edge(pil[i]+based,pil[j],INF);
                add_edge(pil[j]+based,pil[i],INF);
            }
        }
    }

    for(int i=1;i<=r;i++){
        scanf("%s",tmp_s+1); 
        for(int j=1;j<=c;j++){
            if(tmp_s[j]=='L'){
                xcnt++;
                add_edge(Dinic::start,(i-1)*(c+1)+j,1); 
                add_edge((i-1)*(c+1)+j,Dinic::start,0); 
            }
        }
    }

    printf("%d\n",xcnt-Dinic::dinic());
}
