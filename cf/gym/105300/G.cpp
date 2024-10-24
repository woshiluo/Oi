#include <bits/stdc++.h>
using namespace std;
const int Mod=500501;
int n,t=0,Link[100010];
int f[100010][2];
struct edge
{
    int v,nex;
}e[200010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
int ksm(int aa,int bb)
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
void dfs(int now,int fa)
{
    int s=1;f[now][0]=f[now][1]=1;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
        int t0=f[now][0],t1=f[now][1];
        f[now][1]=(1LL*s*f[e[i].v][1]%Mod+1LL*t1*f[e[i].v][0]%Mod)%Mod;
        f[now][0]=(1LL*t0*f[e[i].v][0]%Mod+1LL*t1*f[e[i].v][1]%Mod)%Mod;
        s=1LL*s*f[e[i].v][0]%Mod;
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for (int i=1;i<n;i++) {
        int x,y;
        cin>>x>>y;
        Add_Edge(x,y);
        Add_Edge(y,x);
    }
    dfs(1,0);
    cout<<f[1][0];
    return 0;
}