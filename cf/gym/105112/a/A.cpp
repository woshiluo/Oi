#include <bits/stdc++.h>
using namespace std;
int n;
long long s;
int a[200010],cnt[5];
bool Check(int k)
{
    if (k==1) return 3<=s;
    if (k==2) return 6<=s;
    long long ss=6;
    cnt[0]=cnt[1]=cnt[2]=0;
    for (int i=1;i<=k-2;i++) { 
        cnt[a[i]%3]++;
        ss+=a[i];
    }
    if (cnt[1]>cnt[2]) {
        int t=cnt[1]-cnt[2];
        if (t&1) ss+=t/2+2;
        else ss+=t/2;
    }
    else if (cnt[2]>cnt[1]) ss+=cnt[2]-cnt[1];
    return ss<=s;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>s;s=s*3;
    for (int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    int l=1,r=n;
    while (l<r) {
        int mid=(l+r+1)>>1;
        if (Check(mid)) l=mid;
          else r=mid-1;
    }
    cout<<l;
    return 0;
}