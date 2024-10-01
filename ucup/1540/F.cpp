#include <bits/stdc++.h>
using namespace std;
int t=0,Link[100010],dfn[100010],cnt,f[100010],deg[100010],loop[100010],num;
struct edge
{
    int v,nex;
}e[200010];
void Add_Edge(int x,int y)
{
    e[++t].nex=Link[x];e[t].v=y;Link[x]=t;
    return;
}
void Get_Loop(int now)
{
    dfn[now]=++cnt;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==f[now]) continue;
        if (dfn[e[i].v]) {
            if (dfn[e[i].v]<dfn[now]) continue;
            loop[++num]=e[i].v;
            for (int x=e[i].v;x!=now;x=f[x])
              loop[++num]=f[x]; 
        }
        else f[e[i].v]=now,Get_Loop(e[i].v);
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    for (int i=1;i<=n;i++) {
        int x,y;
        cin>>x>>y;
        Add_Edge(x,y);
        Add_Edge(y,x);
        deg[x]++;deg[y]++;
    }
    Get_Loop(1);
    int s=0,ss=0;
    for (int i=1;i<=n;i++)
      if (deg[i]>4) s++;
        else if (deg[i]<4) ss++;
    loop[num+1]=loop[1];
    long long ans=0;
    if (s==0) {
        for (int i=1;i<=num;i++) {
            int tmp=ss;
            if (deg[loop[i]]==4) tmp++;
            if (deg[loop[i+1]]==4) tmp++;
            ans+=tmp;
        }
    } 
    else if (s==1) {
        for (int i=1;i<=num;i++) {
            if (deg[loop[i]]<=4&&deg[loop[i+1]]<=4) continue;
            int tmp=ss;
            if (deg[loop[i]]==4) tmp++;
            if (deg[loop[i+1]]==4) tmp++;
            ans+=tmp;
        }
    }
    else ans=ss;
    cout<<ans;
    return 0;
}