#include <bits/stdc++.h>
using namespace std;
int a[6],b[6];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while (T--) {
        int ans=0;
        for (int i=1;i<=5;i++) cin>>a[i];
        ans+=a[3]/2+min(a[1],a[5])+min(a[2],a[4]);
        if (a[1]>=a[5]) a[1]-=a[5],a[5]=0;
        else a[5]-=a[1],a[1]=0;
        if (a[2]>=a[4]) a[2]-=a[4],a[4]=0;
        else a[4]-=a[2],a[2]=0;
        a[3]%=2;
        ans+=a[2]/3;
        
        cout<<ans<<'\n';
        int num=0;
        for (int i=1;i<=5;i++)
          if (a[i]) {
              ++num;
              b[num]=i;
          }
        int cnt=a[b[1]];
        for (int i=num;i>=2;i--) {
            int x=min(cnt/(6-b[i]),a[b[i]]);
            ans+=x;
            cnt-=(6-b[i])*x;
            a[b[i]]-=x;
            cnt+=a[b[i]];
        }
        /*if (num==3) {
            int x=min(a[b[1]]/(6-b[num]),a[b[num]]);
            ans+=x;
            a[b[1]]-=(6-b[num])*x;
            a[b[num]]-=x;
            if (!a[b[1]]) b[1]=b[2],b[2]=b[num];
            num--;
        }
        if (num==2) {
            int x=min(a[b[1]]/(6-b[num]),a[b[num]]);
            ans+=x;
            a[b[1]]-=(6-b[num])*x;
            a[b[num]]-=x;
            if (!a[b[1]]) b[1]=b[num];
            num--;
        }
        if (num==1) ans+=a[b[1]]/6;*/
        ans+=cnt/6;
        cout<<ans<<'\n';
    }
    return 0;
}