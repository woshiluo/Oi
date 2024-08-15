#include <bits/stdc++.h>
using namespace std;
int Min[200010],sum[200010],a[200010],b[200010];
vector<int> V[200010];
bool cmp(int p1,int p2)
{
    return Min[p1]<Min[p2];
}
void dfs(int now) 
{
    Min[now]=now;sum[now]=1;
    for (int i=0;i<(int)V[now].size();i++) {
        dfs(V[now][i]);
        Min[now]=min(Min[now],Min[V[now][i]]);
        sum[now]+=sum[V[now][i]];
    }
}
void Solve(int now,int l,int r,int L,int R) 
{
    a[now]=r;b[now]=R;
    int cnt=0;
    for (int i=0;i<(int)V[now].size();i++) {
        int x=V[now][i];
        Solve(x,l+cnt,l+cnt+sum[x]-1,R-1-cnt-sum[x]+1,R-1-cnt);
        cnt+=sum[x];
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n;
        cin>>n;
        for (int i=1;i<=n;i++) V[i].clear();
        for (int i=2;i<=n;i++) {
            int x;
            cin>>x;
            V[x].push_back(i);
        }
        dfs(1);
        for (int i=1;i<=n;i++) sort(V[i].begin(),V[i].end(),cmp);
        Solve(1,1,n,1,n);
        for (int i=1;i<=n;i++) cout<<a[i]<<' '<<b[i]<<' ';
        cout<<'\n';
    }
}