#include <bits/stdc++.h>
using namespace std;
const int N=10;
int p[12],f[505][59055];
bool vis[505][59055];
string str[510];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    p[0]=1;
    for (int i=1;i<=N;i++) p[i]=p[i-1]*3;
    while (T--) {
        int n,K,Mod;
        cin>>n>>K>>Mod;
        for (int i=1;i<=n;i++) {
            cin>>str[i];
            reverse(str[i].begin(),str[i].end());
        }
        for (int i=1;i<=n;i++)
          for (int j=0;j<p[K];j++) f[i][j]=0,vis[i][j]=false;
        f[0][0]=1;vis[0][0]=1;
        for (int i=0;i<n;i++)
          for (int j=0;j<p[K];j++) {
              if (!vis[i][j]) continue;
              f[i+1][j]=(f[i+1][j]+f[i][j])%Mod;
              vis[i+1][j]=true;
              int s=0;
              for (int k=0;k<K;k++) {
                  int t=j/p[k]%3;
                  if (str[i+1][k]=='+') t=(t+1)%3;
                    else if (str[i+1][k]=='-') t=(t-1+3)%3;
                  s+=t*p[k];
              }
              f[i+1][s]=(f[i+1][s]+f[i][j])%Mod;
              vis[i+1][s]=true;
          }
        for (int i=0;i<p[K];i++) 
          if (vis[n][i]) {
              for (int j=K-1;j>=0;j--) {
                  int t=i/p[j]%3;
                  if (t==0) cout<<'A';
                    else if (t==1) cout<<'B';
                      else cout<<'C';
              }
              cout<<' '<<f[n][i];
              cout<<'\n';
          }
    }
    return 0;
}