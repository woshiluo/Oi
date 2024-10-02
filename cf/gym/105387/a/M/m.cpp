#include<bits/stdc++.h>
using namespace std;
int n,a[100010],b[100010];
vector<pair<int,int>>V[100010];
long long ans;
set<int>s;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),s.insert(i);
    for(int i=1;i<=n;i++)
        scanf("%d",&b[i]);
    for(int i=1;i<=n;i++)
        V[a[i]].push_back({b[i],i});
    for(int i=1;i<=n;i++)
        sort(V[i].begin(),V[i].end()),reverse(V[i].begin(),V[i].end());
    memset(a,0,sizeof a);
    for(int i=1;i<=n;i++){
        if(!V[i].size())continue;
        a[V[i][0].second]=i;
        s.erase(i);
    }
    for(int i=1;i<=n;i++)
    if(!a[i])
        s.erase(a[i]=*s.begin()),ans+=b[i];
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
        printf("%d%c",a[i]," \n"[i==n]);
}