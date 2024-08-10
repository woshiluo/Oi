#include <bits/stdc++.h>
using namespace std;
int T,n,a[110],b[110];
int Gcd(int aa,int bb) {return bb?Gcd(bb,aa%bb):aa;}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>T;
    while (T--) {
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        bool fla=true;
        for (int i=2;i<=n;i++) 
          if (a[i]%a[1]) {fla=false;break;}
        if (fla) {
            cout<<n-1<<'\n';
            continue;
        }
        for (int i=n;i>=1;i--)
          for (int j=1;j<i;j++)
            if (a[i]%a[j]==0) {a[i]=0;break;}
        int num=0;
        for (int i=1;i<=n;i++) 
          if (a[i]) b[++num]=a[i];
        fla=false;
        for (int i=1;i<=num;i++)
          for (int j=1;j<i;j++) {
              int t=b[i]%b[j];
              if (!t) continue;
              bool ff=true;
              for (int k=1;k<=num;k++)
                if (k!=i&&b[k]%t) {ff=false;break;}
              if (ff) {fla=true;break;}
          }
        int d=b[2];
        for (int i=3;i<=num;i++) 
          d=Gcd(b[i],d);
        if (b[1]<=d||fla) 
            cout<<n<<'\n';
        else cout<<n+1<<'\n';
    }
    return 0;
}