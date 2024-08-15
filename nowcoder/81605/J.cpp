#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,id[1000010],dfs_clock,sIze[1000010],vis[1000010],fa[1000010];
vector<int>T1[1000010],T2[1000010];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
void dfs2(int x,int F)
{
    id[x]=++dfs_clock;
    sIze[x]=1;fa[x]=F;
    for(int y:T2[x]){
        if(y==F)continue;
        dfs2(y,x);
        sIze[x]+=sIze[y];
    }
}
int check(int RO)
{
    dfs2(RO,dfs_clock=0);
    // cout<<RO<<'\n';
    // for(int i=1;i<=n;i++)
    //     cout<<fa[i]<<" \n"[i==n];
    for(int i=1;i<=n;i++)vis[i]=0;
    for(int x=1;x<=n;x++)
    for(int y:T1[x])if(x<y){
        int xx=x,yy=y;
        if(id[xx]>id[yy])swap(xx,yy);
        if(id[yy]>=id[xx]+sIze[xx])continue;
        while(fa[yy]^xx)
            yy=fa[yy];
        vis[yy]=1;
    }
    for(int i=1;i<=n;i++)
    if(sIze[i]!=1&&!vis[i]&&sIze[i]!=n)
        return 0;
    return 1;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        for(int i=1;i<=n;i++)
            T1[i].clear(),T2[i].clear();
        for(int i=2;i<=n;i++){
            int x=read();
            T1[x].emplace_back(i);
            T1[i].emplace_back(x);
        }
        for(int i=2;i<=n;i++){
            int x=read();
            T2[x].emplace_back(i);
            T2[i].emplace_back(x);
        }
        int ans=-1;
        for(int i=1;i<=n;i++)
        if(check(i)){
            ans=i;//break;
            printf("<%d>",ans);
        }
        printf("\n");
    }
}
/*
<1><2><3><4><5>

<1>
<1><2><3><4>
<1><2><3><4><5>

<1><2><3><4>

<7><10><11>
<1><2><3><4><5><6>
<1><2>

<3><4>

<1><2><3><4><5><6><7>

<1><3>

<3><12>
*/