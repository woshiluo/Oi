#include <bits/stdc++.h>
using namespace std;
int t=1,Link[1010];
struct edge
{
    int v,nex;
}e[2010];
void Insert(int x,int y,int z)
{
    e[++t].nex=Link[x];e[t].v=y;e[t].w=z;Link[x]=t;
}
void dfs(int now)
{
    vis[now]=true;
    for (int i=Link[now];i;i=e[i].nex) {
        if (fla[i]) continue;
        if (vis[])
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,K;
    cin>>n>>m>>K;
    for (int i=1;i<=m;i++) {
        int x,y,z;
        cin>>x>>y>>z;
        Insert(x,y,z);Insert(y,x,z);
    }
    for (int i=1;i<=n;i++) {
        for (int j=1;j<=K;j++) cnt[j]=0;
        int Max=0,deg=0;
        for (int j=Link[i];j;j=e[j].nex) {
            cnt[e[j].w]++;
            Max=max(Max,cnt[e[j].w]);
            deg++;
        }
        if (Max>deg/2||(deg&1)) {
            cout<<-1;
            return 0;
        } 
    }
    dfs(1);
}