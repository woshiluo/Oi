#include <bits/stdc++.h>
using namespace std;
int pr[200010];
long long a[200010],b[200010],mu[200010];
bool vis[200010];
void Sieve(int n)
{
    mu[1]=1;
    int num=0;
    for (int i=2;i<=n;i++) {
        if (!vis[i]) pr[++num]=i,mu[i]=-1;
        for (int j=1;j<=num&&pr[j]<=n/i;j++) {
            vis[i*pr[j]]=true;
            if (i%pr[j]==0) break;
            mu[i*pr[j]]=mu[i]*mu[pr[j]];
        }
    }
    return ;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    Sieve(n);
    for (int i=1;i<=n;i++) cin>>a[i];
    for (int i=1;i<=n;i++) {
        for (int j=1;j*j<=i;j++) 
          if (i%j==0) {
              b[j]+=mu[i/j]*a[i];
              if (i/j!=j) 
                b[i/j]+=mu[j]*a[i];
          }
    }
    while (q--) {
        int ty;
        cin>>ty;
        if (ty==1) {
            int x,y;
            cin>>x>>y;
            for (int i=1;i*i<=x;i++) 
              if (x%i==0) {
                  b[i]-=mu[x/i]*a[x];
                  b[i]+=mu[x/i]*y;
                  if (x/i!=i) {
                      b[x/i]-=mu[i]*a[x];
                      b[x/i]+=mu[i]*y;
                  }
              }
            a[x]=y;
        }
        else {
            int x;
            cin>>x;
            cout<<b[x]<<'\n';
        }
    }
    return 0;
}