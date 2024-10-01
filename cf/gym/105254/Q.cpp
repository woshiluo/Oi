#include <bits/stdc++.h>
using namespace std;
int n;
int a[1000010],c[1000010];
void Add(int x)
{
    for (;x<=n;x+=x&(-x)) c[x]++;
}
int Get(int x)
{
    int res=0;
    for (;x;x-=x&(-x)) res+=c[x];
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    double ans=n+0.5*(n-a[1]);
    for (int i=n;i>=2;i--) {
        int l=min(a[i],a[i-1]),r=max(a[i],a[i-1]);
        int s=Get(r-1)-Get(l),ss=n-i-Get(r);
        ans+=0.5*s+0.5*ss;
        Add(a[i]);
    }
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}