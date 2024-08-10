#include<bits/stdc++.h>
#define LL long long
const int mod=998244353;
using namespace std;
int n,last[200010],num,du[200010],flag,sIze[200010];
int SON[200010],fa[200010];
struct EDGE
{int ver,next;}edge[400010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void add(int X,int Y)
{
    edge[++num]=(EDGE){Y,last[X]};last[X]=num;
}
void dfs(int x,int F)
{
    sIze[x]=1;
    //int SON=0;
    for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver){
        if(y==F)continue;
        SON[x]=y;fa[y]=x;
        dfs(y,x);
        sIze[x]+=sIze[y];
    }
}
void dfs2(int x,int F)
{
   // int SON=0;
    for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver){
        if(y==F)continue;
       // SON=y;
        dfs2(y,x);
    }
    if(du[x]==2&&F){
        int chk1=0,chk2=0;
        if(du[F]==n-sIze[x]||(du[F]==2&&fa[F]&&du[fa[F]]+1==n-sIze[x]))
            chk1=1;
        if(du[SON[x]]==sIze[SON[x]]||(du[SON[x]]==2&&SON[SON[x]]&&du[SON[SON[x]]]==sIze[x]-2))
            chk2=1;
        if(chk1&&chk2)flag=1;
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        memset(du,0,sizeof(int)*(n+5));
        memset(last,0,sizeof(int)*(n+5));
        memset(fa,0,sizeof(int)*(n+5));
        memset(SON,0,sizeof(int)*(n+5));
        num=0;
        for(int i=1;i<n;i++){
            int x=read(),y=read();
            add(x,y);add(y,x);
            du[x]++;du[y]++;
        }
        flag=0;
        for(int i=1;i<=n;i++)
        if(du[i]==1){
            //cout<<"FUCK "<<i<<"\n";
            dfs(i,0);dfs2(i,0);break;
        }
        if(flag)printf("Yes\n");
        else printf("No\n");
    }
}