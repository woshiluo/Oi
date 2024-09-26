#include <bits/stdc++.h>
using namespace std;
int t=0,Link[200010],Max[200010][2],mx[200010],deg[200010],f[200010];
long long a[200010],aa[200010],b[200010],bb[200010],ans;
struct edge
{
    int v,nex;
}e[400010];
void Insert(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return ;
}
void dfs(int now,int fa)
{
    int x=0,y=0;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        dfs(e[i].v,now);
        if (Max[e[i].v][0]+1>Max[now][0]) {
            Max[now][1]=Max[now][0];
            Max[now][0]=Max[e[i].v][0]+1;
        }
        else Max[now][1]=max(Max[now][1],Max[e[i].v][0]+1);
        if (!x) x=e[i].v;
          else y=e[i].v;
    }
    if (!x) a[now]=1,b[now]=0;
    else if (!y) a[now]=2*a[x]+1,b[now]=b[x];
    else a[now]=2*a[x]+2*a[y]+1,b[now]=b[x]+b[y]+min(a[x],a[y]);
    return;
}
void dfs1(int now,int fa)
{
    if (fa&&deg[now]<3) {
        long long A=0,B=0;
        int x=0;
        for (int i=Link[now];i;i=e[i].nex)
          if (e[i].v!=fa) x=e[i].v;
        if (!x&&mx[now]<33) 
            ans=min(ans,aa[now]+bb[now]);
          else if (max(mx[now],Max[now][0])<32){
            A=2*aa[now]+2*a[x]+1,B=bb[now]+b[x]+min(aa[now],a[x]);
            ans=min(ans,A+B);
          }
    }
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        if (Max[now][0]==Max[e[i].v][0]+1) mx[e[i].v]=max(mx[now],Max[now][1])+1;
          else mx[e[i].v]=max(mx[now],Max[now][0])+1;
        int x=0;
        for (int j=Link[now];j;j=e[j].nex) 
            if (j!=i&&e[j].v!=fa) x=e[j].v;
        if (!fa&&!x) aa[e[i].v]=1,bb[e[i].v]=0;
          else if (!fa&&x) aa[e[i].v]=2*a[x]+1,bb[e[i].v]=b[x];
            else if (fa&&!x) aa[e[i].v]=2*aa[now]+1,bb[e[i].v]=bb[now];
              else aa[e[i].v]=2*aa[now]+2*a[x]+1,bb[e[i].v]=bb[now]+b[x]+min(aa[now],a[x]);
        dfs1(e[i].v,now);
    }
}
int Find(int x) {return f[x]==x?x:f[x]=Find(f[x]);}
bool Solve()
{
    int n,m;
    cin>>n>>m;
    if (m>n-1) return false;
    if (n==1) {
        ans=0;
        return true;
    }
    for (int i=1;i<=n;i++) f[i]=i;
    for (int i=1;i<n;i++) {
        int x,y;
        cin>>x>>y;
        if (Find(x)==Find(y)) return false;
        f[Find(x)]=Find(y);
        deg[x]++;deg[y]++;
        Insert(x,y);Insert(y,x);
    }
    int rt=0;;
    for (int i=1;i<=n;i++) {
        if (deg[i]>3) return false;
        if (deg[i]<3) rt=i;
    } 
    dfs(rt,0);
    // cout<<rt<<'\n';
    // for (int i=1;i<=n;i++) cout<<a[i]<<' '<<b[i]<<'\n';
    for (int i=1;i<=n;i++) 
      if (Max[i][0]+Max[i][1]>62) return false;
    ans=1e18;
    if (deg[rt]==1&&Max[rt][0]<33) {
        int x=e[Link[rt]].v;
        ans=min(ans,a[x]+b[x]);
    }
    else if (Max[rt][0]<32) ans=min(ans,a[rt]+b[rt]);
    aa[rt]=1;bb[rt]=0;
    dfs1(rt,0);
    if (ans==1e18) return false;
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!Solve()) cout<<"NIE";
      else cout<<ans;
    return 0;
}