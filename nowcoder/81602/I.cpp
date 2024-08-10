#include <bits/stdc++.h>
using namespace std;
int m,k,h;
bool Check(int s)
{
    int t;
    if (m==k&&s>=m) return true;
    if (s<m) t=0;
      else t=(s-m)/(m-k)+1;
    if (1LL*t*k+s>=h) return true;
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        cin>>m>>k>>h;
        int l=0,r=1e9;
        while (l<r) {
            int mid=(l+r)>>1;
            if (Check(mid)) r=mid;
              else l=mid+1;
        }
        cout<<l<<'\n';
    }
    return 0;
}