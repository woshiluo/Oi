#include <bits/stdc++.h>
using namespace std;
__int128 f[35],g[65],p[35];
void Pre()
{
    __int128 v=1;
    p[0]=1;
    for (int i=1;i<=31;i++) p[i]=p[i-1]*10;
    for (int i=1;i<=30;i++) {
        v=v*10;
        __int128 l=0,r=1e15;
        while (l<r) {
            __int128 mid=(l+r+1)>>1;
            if (mid*mid<v) l=mid;
              else r=mid-1;
        }
        f[i]=l+1;
    }
    for (int i=2;i<=60;i+=2)
      g[i]=f[i/2]*f[i/2];
}
__int128 Find(__int128 lim,int op)
{
    __int128 l=0,r=1e15;
    while (l<r) {
        __int128 mid=(l+r+op)>>1;
        if (op==0) {
            if (mid*mid>=lim) r=mid;
              else l=mid+1;
        }
        else {
            if (mid*mid<=lim) l=mid;
              else r=mid-1;
        }
    }
    return l;
}
void Print(__int128 res)
{
    if (!res) return ;
    Print(res/10);
    int c=res%10;
    cout<<c;
}
__int128 Calc(int n,string A)
{
    __int128 res=0;
    int m=n/2;__int128 tmp=0;
    for (int i=n-1;i>=n-m;i--) {
        int c=A[i]-'0';
        for (int j=0;j<c;j++) {
            __int128 v=tmp*10+j;
            __int128 l=Find(v*p[i-n+m],0),r=Find(v*p[i-n+m]+p[i-n+m]-1,1);
            if (l>r) continue;
            res+=(r-l+1)*f[m];
        }
        tmp=tmp*10+c;
    }
    // Print(res);cout<<endl;
    __int128 k=Find(tmp,0);
    if (k*k!=tmp) return res;
    tmp=0;
    for (int i=n-m-1;i>=0;i--) {
        int c=A[i]-'0';
        for (int j=0;j<c;j++) {
            __int128 v=tmp*10+j;
            __int128 l=Find(v*p[i],0),r=Find(v*p[i]+p[i]-1,1);
            if (l>r) continue;
            res+=(r-l+1);
        }
        tmp=tmp*10+c;
    }
    k=Find(tmp,0);
    if (k*k==tmp) res++;
    return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Pre();
    int n;
    cin>>n;
    string L,R;
    cin>>L>>R;
    reverse(L.begin(),L.end());
    reverse(R.begin(),R.end());
    int len=(int)L.size();
    int tmp=1;
    for (int i=0;i<len;i++) 
      if (L[i]-'0'<tmp) {
          L[i]=L[i]+10-tmp;
          tmp=1;
      }
      else {L[i]=L[i]-tmp;break;}
    // if (L[len-1]=='0') {
    //     __int128 res=Calc(n,R);
    //     // if (res==0) cout<<0;
    //     //   else Print(res);
    //     return 0;
    // }
    __int128 res=Calc(n,R)-Calc(n,L);
    if (res==0) cout<<0;
      else Print(res);
}