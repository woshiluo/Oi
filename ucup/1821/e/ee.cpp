#include <bits/stdc++.h>
using namespace std;
const long long Mod=998244353;
int t,Link[100010],f[100010],sum=0;
bool vis[100010];
int n,Q;
struct edge
{
    int v,nex;
}e[100010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
void Calc(int now,int fa)
{
    f[now]=1;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        if (vis[e[i].v]) continue;
        Calc(e[i].v,now);
        f[now]=1LL*f[now]*(f[e[i].v]+1)%Mod;
    }
    sum=(sum+f[now])%Mod;
}
bool dfs(int now,int fa,int ed) 
{
    vis[now]=false;
    if (now==ed) {
        vis[now]=true;
        return true;
    }
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        if (dfs(e[i].v,now,ed)) {
            vis[now]=true;
            return true;
        }
    }
    return false;
}
int main()
{
	freopen( "e.in", "r", stdin );
	freopen( "e.ans", "w", stdout );
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
            cin>>x;
            Add_Edge(x,i);
            Add_Edge(i,x);
        }
        for (int i=1;i<=n;i++) vis[i]=false;
        sum=0;Calc(1,0);int res=sum;
        while (Q--) {
            int x,y;
            cin>>x>>y;
            sum=0;
            for (int i=1;i<=n;i++) vis[i]=false;
            dfs(x,0,y);
            for (int i=1;i<=n;i++) f[i]=0;
            for (int i=1;i<=n;i++)
              if (!vis[i]&&!f[i]) Calc(i,0);
            cout<<(res-sum+Mod)%Mod<<'\n';
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
