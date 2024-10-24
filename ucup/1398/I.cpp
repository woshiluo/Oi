#include <bits/stdc++.h>
using namespace std;
int n;
long long a[100010];
bool Check(int lim)
{
    priority_queue<long long> q;
    for (int i=n;i>=n-lim+1;i--) 
      if (a[i]>1) q.push(a[i]/2);
    for (int i=n-lim;i>=1;i--) {
        if (!q.size()) return false;
        long long x=q.top();q.pop();
        if (a[i]>x) return false;
        if (a[i]>1) q.push(a[i]/2);
        if (x-a[i]>0) q.push(x-a[i]);
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        int l=1,r=n;
        while (l<r) {
            int mid=(l+r)>>1;
            if (Check(mid)) r=mid;
              else l=mid+1;
        }
        cout<<l<<'\n';
    }
    return 0;
}