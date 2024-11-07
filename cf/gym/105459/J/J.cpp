#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010];
pair<int,int>p[100010];
long long solve()
{
    long long sum,Max=0;
    for(int i=1;i<=n;i++)Max+=a[i];
    sum=Max;
    for(int i=1;i<=m;i++){
        if(sum<p[i].first-p[i-1].first)
            return p[i-1].first+sum;
        sum=min(sum-(p[i].first-p[i-1].first)+a[p[i].second],Max);
    }
    return p[m].first+sum;
}
int main()
{
    cin.tie(0)->sync_with_stdio(false);
    int T;cin>>T;
    while(T --> 0){
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=m;i++)
            cin>>p[i].first>>p[i].second;
        cout<<solve()<<endl;
    }
}