#include <bits/stdc++.h>
using namespace std;
long long a[200010];
long long c(int s,int k,int t)
{
    return 1LL*(t-s+1+t)*s/2*k;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int n,p;
        cin>>n>>p;
        for (int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
        int k,t;
        cin>>k>>t;
        long long ans=0;
        for (int i=0;i<=p-1&&2*i<t;i++) {
            int x=p-i,y=min(t-1-2*i+p,n);
            ans=max(ans,c(y-x+1,k,t)+a[y]-a[x-1]);
        }
        for (int i=0;i<=n-p&&2*i<t;i++) {
            int y=p+i,x=max(1,p-(t-1-2*i));
            ans=max(ans,c(y-x+1,k,t)+a[y]-a[x-1]);
        }
        cout<<ans<<'\n';
    }
    return 0;
}