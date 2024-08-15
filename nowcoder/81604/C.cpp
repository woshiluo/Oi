#include <bits/stdc++.h>
using namespace std;
const int Mod=1e9+7;
int rr[100010],cc[100010];
long long r[100010],c[100010];
vector<int> vc,vr;
int gcd(int aa,int bb) {return bb?gcd(bb,aa%bb):aa;}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    for (int d=1;d<=n;d++)
      for (int i=d;i<=n;i+=d)
        for (int j=d;j<=n;j+=d) 
          if (gcd(i,j)==d) r[i]+=d,c[i]+=d; 
    for (int i=1;i<=n;i++) rr[i]=cc[i]=1,r[i]%=Mod,c[i]%=Mod;
    int res=0;
    for (int i=1;i<=n;i++) res=(res+r[i])%Mod;
    // for (int i=1;i<=n;i++) cout<<r[i]<<endl;
    while (q--) {
        string str;
        int x,v;
        cin>>str>>x>>v;
        if (str[0]=='R') {
            int tmp=1LL*r[x]*rr[x]%Mod;
            for (int i=0;i<(int)vc.size();i++) {
                int y=vc[i];
                int val=gcd(x,y);
                tmp-=1LL*val*rr[x]%Mod;tmp=(tmp+Mod)%Mod;
                tmp+=1LL*val*rr[x]%Mod*cc[y]%Mod;tmp%=Mod;
            }
            res-=tmp;res=(res+Mod)%Mod;
            rr[x]=1LL*rr[x]*v%Mod;
            tmp=1LL*r[x]*rr[x]%Mod;
            for (int i=0;i<(int)vc.size();i++) {
                int y=vc[i];
                int val=gcd(x,y);
                tmp-=1LL*val*rr[x]%Mod;tmp=(tmp+Mod)%Mod;
                tmp+=1LL*val*rr[x]%Mod*cc[y]%Mod;tmp%=Mod;
            }
            res=(res+tmp)%Mod;
            vr.push_back(x);
        }
        else {
            int tmp=1LL*c[x]*cc[x]%Mod;
            for (int i=0;i<(int)vr.size();i++) {
                int y=vr[i];
                int val=gcd(x,y);
                tmp-=1LL*val*cc[x]%Mod;tmp=(tmp+Mod)%Mod;
                tmp+=1LL*val*cc[x]%Mod*rr[y]%Mod;tmp%=Mod;
            }
            res-=tmp;res=(res+Mod)%Mod;
            cc[x]=1LL*cc[x]*v%Mod;
            tmp=1LL*c[x]*cc[x]%Mod;
            for (int i=0;i<(int)vr.size();i++) {
                int y=vr[i];
                int val=gcd(x,y);
                tmp-=1LL*val*cc[x]%Mod;tmp=(tmp+Mod)%Mod;
                tmp+=1LL*val*cc[x]%Mod*rr[y]%Mod;tmp%=Mod;
            }
            res=(res+tmp)%Mod;
            vc.push_back(x);
        }
        cout<<res<<'\n';
    }
    return 0;
}