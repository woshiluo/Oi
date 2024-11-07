#include <bits/stdc++.h>
using namespace std;
const long long Mod=998244353;
int t,Link[100010];
long long f[100010],fs[100010],g[100010],gs[100010],sf[100010];
int n,Q,fa[100010][20];
int dep[100010],pre[100010],suf[100010];
struct edge
{
    int v,nex;
}e[100010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
int ksm(int aa,int bb)
{
    long long res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
void dfs(int now)
{
    f[now]=1;fs[now]=0;
    for (int i=Link[now];i;i=e[i].nex) {
        dep[e[i].v]=dep[now]+1;
        dfs(e[i].v);
        f[now]=1LL*f[now]*(f[e[i].v]+1)%Mod;
        fs[now]=(fs[now]+fs[e[i].v])%Mod;
        fs[now]=(fs[now]+f[e[i].v])%Mod;
    }
}
void dfs1(int now)
{
    int num=0;pre[0]=1;vector<int> V;
    for (int i=Link[now];i;i=e[i].nex) {
        V.push_back(e[i].v);
        ++num;
        pre[num]=1LL*pre[num-1]*(f[e[i].v]+1)%Mod;
    }
    suf[num+1]=1;
    for (int i=num;i>=1;i--) 
        suf[i]=1LL*suf[i+1]*(f[V[i-1]]+1)%Mod;
    num=0;
    for (int i=Link[now];i;i=e[i].nex) {
        num++;
        g[e[i].v]=1LL*pre[num-1]%Mod*suf[num+1]%Mod*(g[now]+1)%Mod;
        gs[e[i].v]=(long long)((gs[now]+fs[now]-fs[e[i].v]-f[e[i].v]+g[e[i].v])%Mod+Mod)%Mod;
        sf[e[i].v]=(sf[now]+f[e[i].v])%Mod;
    }
    for (int i=Link[now];i;i=e[i].nex) dfs1(e[i].v);
}
void Init()
{
    for (int i=1;i<=16;i++)
      for (int j=1;j<=n;j++)
        fa[j][i]=fa[fa[j][i-1]][i-1];
    return ;
}
int Get_Lca(int x,int y)
{
    if (dep[x]>dep[y]) swap(x,y);
    int d=dep[y]-dep[x];
    for (int i=0;i<=16;i++)
      if (d>>i&1) y=fa[y][i];
    if (x==y) return x;
    for (int i=16;i>=0;i--)
      if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int main()
{
	freopen( "e.in", "r", stdin );
	freopen( "e.out", "w", stdout );
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n>>Q;
        t=0;
        for (int i=1;i<=n;i++) Link[i]=0;
        for (int i=2;i<=n;i++) {
            int x;
            cin>>x;fa[i][0]=x;
            Add_Edge(x,i);
        }
        dfs(1);
        g[1]=0;gs[1]=0;
        sf[1]=f[1];dfs1(1);
        Init();
        // for (int i=1;i<=n;i++) cout<<i<<' '<<f[i]<<' '<<sf[i]<<'\n';
        long long sum=(fs[1]+f[1])%Mod;
        while (Q--) {
            int x,y;
            cin>>x>>y;
            int k=Get_Lca(x,y);
            long long ans=((fs[k]-(sf[x]-sf[k])-(sf[y]-sf[k])+gs[k])%Mod+Mod)%Mod;
            // cout<<sf[x]<<' '<<sf[k]<<' '<<sf[y]<<' '<<sf[k]<<'\n';
            cout<<(sum-ans+Mod)%Mod<<'\n';
        }
    }
    return 0;
}
/*

3 2
1 1
2 3
1 2
*/
