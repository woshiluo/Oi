#include <bits/stdc++.h>
using namespace std;
int n,K,s[200010],f[200010],a[200010];
const int pri[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103};
bool Check(int lim) 
{
    for (int i=1;i<=n;i++) {
        f[i]=f[i-1];
        for (int j=0;j<25&&pri[j]<=i;j++) 
          if (s[i]-s[i-pri[j]]>=lim) {
            f[i]=max(f[i],f[i-pri[j]]+1);break;
          }
        if (f[i]>=K) return true;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n>>K;
        for (int i=1;i<=n;i++) {
            cin>>a[i];
            s[i]=s[i-1]+a[i];
        }
        int l=-2e8,r=2e8;
        while (l<r) {
            int mid=(l+r+1)>>1;
            if (Check(mid)) l=mid;
              else r=mid-1;
        }
        if (Check(l)) cout<<l<<'\n';
          else cout<<"impossible"<<'\n';
    }
    return 0;
}