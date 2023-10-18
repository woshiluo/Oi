#include<iostream>
#include<cstdio>
#include<vector>
#define int long long
using namespace std;
const int N=200005;
int n;
int a[N];
vector<int>G[N];
int siz[N];
int f[N][2],g[N][2];
int c[N];
void dfs1(int u,int father)
{
    f[u][c[u]]=0;
    siz[u]=1;
    for(int v:G[u])
    {
        if(v==father) continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        f[u][c[u]]+=f[v][c[u]];
    }
    f[u][c[u]^1]=f[u][c[u]]+siz[u];
    return;
}
void dfs2(int u,int father)
{
    for(int v:G[u])
    {
        if(v==father) continue;
        g[v][c[v]]=g[u][c[u]]+f[u][c[u]]-f[v][c[u]]+(c[u]!=c[v])*(n-siz[v]);
        g[v][c[v]^1]=g[v][c[v]]+n-siz[v];
        dfs2(v,u);
    }
    return;
}
long long res[N];
void solve()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        G[i].clear();
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].emplace_back(y);
        G[y].emplace_back(x);
    }
    for(int i=1;i<=n;i++)
        res[i]=0;
    for(int j=0;j<20;j++)
    {
        for(int i=1;i<=n;i++)
            c[i]=((a[i]>>j)&1);
        dfs1(1,0);
        g[1][c[1]]=0,g[1][c[1]^1]=1;
        dfs2(1,0);
        for(int i=1;i<=n;i++)
            res[i]+=(long long)(1<<j)*(f[i][c[i]]+g[i][c[i]]);
    }
    for(int i=1;i<=n;i++)
        printf("%lld ",res[i]);
    printf("\n");
    return;
}
signed main()
{
    int T;
    scanf("%lld",&T);
    while(T--)
        solve();
    return 0;
}
