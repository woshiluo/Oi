#include<bits/stdc++.h>
using namespace std;
int n,m,sIze[100010],son[100010],dep[100010],fa[100010],top[100010],id[100010],f[100010];
vector<int>G[100010];
void dfs(int x,int F)
{
    sIze[x]=1;son[x]=0;
    for(int y:G[x]){
        if(y==F)continue;
        dep[y]=dep[fa[y]=x]+1;
        dfs(y,x);
        sIze[x]+=sIze[y];
        if(sIze[y]>sIze[son[x]])
            son[x]=y;
    }
}
void dfs(int x,int F,int Top)
{
    top[x]=Top;
    if(son[x])dfs(son[x],x,Top);
    for(int y:G[x]){
        if(y==F||y==son[x])continue;
        dfs(y,x,y);
    }
}
int lca(int x,int y)
{
    while(top[x]^top[y])
        dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
    return dep[x]<dep[y]?x:y;
}
void dp(int x,int F)
{
    // cout<<"<"<<x<<">\n";
    id[x]=0;
    if(!son[x])id[x]=(x+1)%m+1;
    for(int y:G[x]){
        if(y==F)continue;
        dp(y,x);
        if(!id[x])id[x]=id[y];
        else id[x]=lca(id[x],id[y]);
    }
}
void DP(int x,int F)
{
    f[x]=0;
    if(!son[x])f[x]=1;
    if(x!=1&&dep[x]<=dep[id[x]])
        return;
    for(int y:G[x]){
        if(y==F)continue;
        DP(y,x);
        if(f[y])f[x]=1;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;cin>>T;
    while(T --> 0){
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            G[i].clear();
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            G[x].emplace_back(y);
            G[y].emplace_back(x);
        }
        dfs(n,dep[n]=1);
        dfs(n,0,n);
        dp(n,0);
        DP(n,0);
        for(int i=1;i<=n;i++)
        cout<<'<'<<i<<','<<id[i]<<','<<f[i]<<">\n";
        cout<<(f[n]?"Tie\n":"Doddle\n");
    }
}