#include <bits/stdc++.h>
using namespace std;
const int N=1e5;
int num,pr[N+10];
bool vis[N+10];
void Sieve()
{
    for (int i=2;i<=N;i++) {
        if (!vis[i]) vis[i]=true,pr[++num]=i;
        for (int j=1;j<=num&&pr[j]<=N/i;j++) {
            vis[i*pr[j]]=true;
            if (i%pr[j]==0) break;
        }
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    Sieve();
    cin>>T;
    while (T--) {
        long long n;
        cin>>n;
        int lim=sqrt(n);
        long long ans=1;
        for (int i=1;i<=num&&pr[i]<=lim;i++) 
          if (n%pr[i]==0) {
              int cnt=0;
              while (n%pr[i]==0) {
                  n/=pr[i];
                  cnt++;
              }
              ans=ans*(1+2*cnt);
          }
        if (n>1) ans=ans*3;
        ans=(ans-1)/2+1;
        cout<<ans<<'\n';
    }
    return 0;
}