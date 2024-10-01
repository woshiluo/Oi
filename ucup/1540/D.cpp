#include <bits/stdc++.h>
using namespace std;
int t=0,Link[100010],f[100010][18],n,m,dep[100010];
int fla[100010],c[100010];
bool dp[100010];
struct edge
{
    int v,nex;
}e[200010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
void dfs(int now,int fa)
{
    f[now][0]=fa;dep[now]=dep[fa]+1;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
    }
    return ;
}
void dfs1(int now,int fa)
{
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs1(e[i].v,now);
        fla[now]=fla[now]+fla[e[i].v];
    }
    return ;
}
void Init()
{
    for (int i=1;i<=16;i++)
      for (int j=1;j<=n;j++)
        f[j][i]=f[f[j][i-1]][i-1];
    return ;
}
int Get_Lca(int x,int y)
{
    if (dep[y]>=dep[x]) { 
        int d=dep[y]-dep[x];
        for (int i=0;i<=16;i++)
          if (d>>i&1) y=f[y][i];
    }
    else {
        int d=dep[x]-dep[y];
        for (int i=0;i<=16;i++)
          if (d>>i&1) x=f[x][i];
    }
    if (x==y) return x;
    for (int i=16;i>=0;i--)
      if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return x;
}
void Solve(int now,int fa)
{
    dp[now]=true;bool ff=false;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        ff=true;
        Solve(e[i].v,now);
        fla[e[i].v]+=c[e[i].v];
        if (fla[e[i].v]&&!dp[e[i].v]) dp[now]=false; 
    }
    if (!ff) dp[now]=false;
    // cout<<now<<' '<<fla[now]<<' '<<dp[now]<<'\n';
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n>>m;
        t=0;
        for (int i=1;i<=n;i++) 
          Link[i]=0,fla[i]=0,c[i]=0;
        for (int i=1;i<n;i++) {
            int x,y;
            cin>>x>>y;
            Add_Edge(x,y);Add_Edge(y,x);
        }
        dfs(n,0);Init();
        for (int i=1;i<=m;i++) {
            int k=Get_Lca(i,i==m?1:i+1);
            if (k==i) fla[f[k][0]]++;
              else fla[i]++,c[k]--;  
        }
        dfs1(n,0);
        Solve(n,0);
        if (!dp[n]) cout<<"Tie"<<'\n';
          else cout<<"Doddle"<<'\n';
    }
    return 0;
};
/*
3
5 4
1 5
2 5
3 5
4 5
6 3
1 4
2 4
3 5
5 6
4 6
5 4
1 5
2 5
3 5
4 5
*/