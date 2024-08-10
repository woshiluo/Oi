#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m,cnt,du[500010],tot[500010],vis[500010],id[500010],DUOSHAOGE[500010];
vector<int>G[500010],V[500010][2];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void dfs(int x,int F,int DEP)
{
    tot[cnt]++;vis[x]=1;
    V[cnt][DEP].emplace_back(x);
    for(int y:G[x]){
        if(y==F)continue;
        dfs(y,x,DEP^1);
    }
}
int cmp(int n1,int n2)
{return DUOSHAOGE[n1]>DUOSHAOGE[n2];}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();m=read();cnt=0;
        for(int i=1;i<=n;i++)
            G[i].clear(),tot[i]=du[i]=vis[i]=0,V[i][0].clear(),V[i][1].clear();
        for(int i=1;i<=m;i++){
            int x=read(),y=read();
            du[x]++;du[y]++;
            G[x].emplace_back(y);
            G[y].emplace_back(x);
        }
        if(n==1){
            printf("1\n");
            continue;
        }
        for(int i=1;i<=n;i++)
        if(!vis[i]){
            cnt++;
            dfs(i,0,0);
            DUOSHAOGE[cnt]=!!V[cnt][0].size()+!!V[cnt][1].size();
        }
        if(cnt>1){
            iota(id+1,id+1+cnt,1);
            sort(id+1,id+1+cnt,cmp);
            for(int i=1;i<=cnt;i++)
            for(auto x:V[id[i]][0])
                printf("%d ",x);
            for(int i=1;i<=cnt;i++)
            for(auto x:V[id[i]][1])
                printf("%d ",x);
            printf("\n");
        }else{
            bool flag=0;
            if(V[1][0].size()<V[1][1].size())
                swap(V[1],V[0]);
            for(int x:V[1][0])if(du[x]<V[1][1].size()){
                for(int y:G[x])vis[y]=0;
                for(int y:V[1][1]){
                    if(!vis[y])continue;
                    for(int z:V[1][0])
                    if(z!=x)
                        printf("%d ",z);
                    printf("%d ",x);
                    printf("%d ",y);
                    for(int z:V[1][1])
                    if(z!=y)
                        printf("%d ",z);
                    printf("\n");
                    flag=1;
                    break;
                }
                if(flag)break;
            }
            if(!flag)
                printf("-1\n");
        }
    }
}
