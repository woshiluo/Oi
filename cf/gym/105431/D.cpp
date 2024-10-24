#include <bits/stdc++.h>
using namespace std;
int a[150010],n,K,N;
int c[150010],f[20];
vector<int> V[10010];
int Get(int x)
{
    int res=0;
    for (;x;x-=x&(-x)) res=max(res,c[x]);
    return res;
}
void Add(int x,int val)
{
    for (;x<=N;x+=x&(-x)) c[x]=max(c[x],val);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>K;
    N=n*K;
    for (int i=1;i<=N;i++) cin>>a[i];
    for (int i=1;i<=N;i++) {
        int x;
        cin>>x;
        V[x].push_back(i);
    }
    int ans=0;
    for (int i=1;i<=N;i++) {
        for (int j=1;j<=K;j++) {
            f[j]=Get(V[a[i]][j-1]-1)+1;
            ans=max(ans,f[j]);
        }
        for (int j=1;j<=K;j++)
          Add(V[a[i]][j-1],f[j]);
    }
    cout<<ans;
    return 0;
}