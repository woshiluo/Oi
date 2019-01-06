#include <cstdio>

const int N=110;

int n,m,vcnt;
int vis[N],match[N];
char s[N][N];
int dx[3]={0,-1};
int dy[3]={-1,0};

// edge start
struct edge{
    int to,next;   
}e[N*N<<2];
int ehead[N*N],ecnt;
inline void add_edge(int now,int to){
    ecnt++;
    e[ecnt].to=to;
    e[ecnt].next=ehead[now];
    ehead[now]=ecnt;
}
// edge end

bool eft(int now){
    
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]+1);                
        for(int j=1;j<=m;j++){
            for(int k=0;k<3;k++){
                if(s[i+dx[k]][j+dy[k]]=='.'){
                    add_edge((i+dx[k])*n+(j+dy[k]),i*n+m);
                    add_edge(i*n+m,(i+dx[k])*n+(j+dy[k]));
                }
            }                                    
        }
    }
    for(int i=1;i<=n;i++){
         
    }
    
}
