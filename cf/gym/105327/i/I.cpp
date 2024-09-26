#include <bits/stdc++.h>
using namespace std;
const int N=1e6,Mod=1e9+7;
int f[N+10],cnt[N+10],pr[N+10],mu[N+10];
bool vis[N+10];
int ksm(int aa,int bb) 
{
    int res=1;
    for (;bb;bb>>=1) {
        if (bb&1) res=1LL*res*aa%Mod;
        aa=1LL*aa*aa%Mod;
    }
    return res;
}
void Sieve()
{
    int num=0;
    for (int i=2;i<=N;i++) {
        if (!vis[i]) pr[++num]=i,mu[i]=-1;
        for (int j=1;j<=num&&pr[j]<=N/i;j++) {
            vis[i*pr[j]]=true;
            mu[i*pr[j]]=-mu[i];
            if (i%pr[j]==0) {
                mu[i*pr[j]]=0;
                break;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Sieve();
    int n;
    cin>>n;
    for (int i=1;i<=n;i++) {
        int x;
        cin>>x;
        cnt[x]++;
    }
    for (int i=1;i<=N;i++) f[i]=n; 
    for (int i=2;i<=N;i++) 
      if (mu[i]!=0) {
          int s=0;
          for (int j=i;j<=N;j+=i)
            s+=cnt[j];
          for (int j=i;j<=N;j+=i) 
            f[j]+=mu[i]*s;
      }
    int Q;
    cin>>Q;
    while (Q--) {
        int x;
        cin>>x;
        cout<<ksm(2,f[x])<<'\n';
    }
    return 0;
}