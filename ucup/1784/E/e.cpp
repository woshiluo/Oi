#include<bits/stdc++.h>
using namespace std;
int n,last[5010],num,cnt,dfs_clock,top,du[5010];
int dfn[5010],low[5010],st[5010],id[5010],vis[5010];
char str[5010][5010];
vector<int>V[5010];
struct EDGE
{int ver,next;}edge[25000010];
inline int read()
{
    int x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void add(int X,int Y)
{edge[++num]=(EDGE){Y,last[X]};last[X]=num;}
void tarjan(int x)
{
    dfn[st[++top]=x]=low[vis[x]=x]=++dfs_clock;
    for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
    if(!dfn[y]){
        tarjan(y);
        low[x]=min(low[x],low[y]);
    }else if(vis[y])
        low[x]=min(low[x],dfn[y]);
    if(low[x]==dfn[x]){
        int y;cnt++;
        do{
            vis[y=st[top--]]=0;
            V[id[y]=cnt].emplace_back(y);
        }while(x^y);
    }
}
bool cmp(int n1,int n2)
{
    return du[n1]>du[n2];
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        scanf("%s",str[i]+1);
        for(int j=1;j<=n;j++)
        if(str[i][j]&1)
            add(i,j);
    }
    for(int i=1;i<=n;i++)
    if(!dfn[i])
        tarjan(i);
    for(int x=1;x<=n;x++)
    for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
        if(id[x]^id[y])
            du[id[y]]++;
    for(int i=1;i<=cnt;i++)
    if(du[i]==0){
        memset(du,0,sizeof du);
        for(int x=1;x<=n;x++)
        for(int j=last[x],y=edge[j].ver;j;j=edge[j].next,y=edge[j].ver)
            if(id[x]==id[y])
                du[id[y]]++;
        sort(V[i].begin(),V[i].end(),cmp);
        if(V[i].size()<=3)
            printf("NOT FOUND\n");
        else printf("%d %d %d\n",V[i][0],V[i][1],V[i][2]);
        break;
    }
}