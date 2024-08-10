#include <bits/stdc++.h>
using namespace std;
double f[200010],c[200010];
int Link[200010],sum0[200010],t,sum1[200010];
struct edge
{
    int v,nex,w;
}e[400010];
void Insert(int x,int y,int z) 
{
    e[++t].nex=Link[x];e[t].v=y;e[t].w=z;Link[x]=t;
    return ;
}
void dfs(int now,int fa)
{
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        sum0[e[i].v]=sum0[now];sum1[e[i].v]=sum1[now];
        if (e[i].w==0) sum0[e[i].v]++;
          else sum1[e[i].v]++;    
        dfs(e[i].v,now);   
    }
    return ;
}
void dfs1(int now,int fa,int op)
{
    if (op==0) f[now]=0;
      else f[now]=1;
    bool fla=false;
    for (int i=Link[now];i;i=e[i].nex) {
        if (e[i].v==fa) continue;
        if (now==1&&e[i].w==0) continue;
        fla=true;
        dfs1(e[i].v,now,op^1);
        if (op==0) f[now]=max(f[now],f[e[i].v]);
          else f[now]=min(f[now],f[e[i].v]);
    }
    if (!fla) f[now]=c[now];
    else if (now!=1) f[now]=min(f[now],c[now]);
    // cout<<now<<' '<<f[now]<<endl;
}
int main()
{
    int T;
    scanf("%d",&T);
    while (T--) {
        int n;
        scanf("%d",&n);
        t=0;
        for (int i=1;i<=n;i++) Link[i]=0;
        for (int i=1;i<n;i++) {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            Insert(x,y,z);Insert(y,x,z);
        }
        bool fla=false;
        for (int i=Link[1];i;i=e[i].nex)
          if (e[i].w==1) {fla=true;break;}
        // cout<<fla<<endl;
        if (!fla) {
            puts("0");
            continue;
        }
        dfs(1,0);
        for (int i=2;i<=n;i++) c[i]=(double)sum1[i]/(sum0[i]+sum1[i]);
        dfs1(1,0,0);
        printf("%.9lf\n",f[1]);
    }
}