#include <bits/stdc++.h>
using namespace std;
int m,n,p[20],a[20][20],las[20];
long long f[18][18][100010];
long long ans[200010];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>m>>n;
    for (int i=0;i<=m;i++) p[i]=(1<<i); 
    for (int i=0;i<m;i++)
      for (int j=0;j<m;j++) 
        cin>>a[i][j];
    string str;
    cin>>str;
    for (int i=0;i<m;i++) las[i]=-1;
    for (int i=0;i<n;i++) {
        int c=str[i]-'a';
        for (int j=0;j<m;j++)
          if (las[j]!=-1&&(las[j]>las[c]||j==c)) {
              int s=0;
              if (c==j) s=(1<<(m-1))-1;
                else s=(1<<(m-2))-1;
              for (int k=0;k<m;k++) {
                if (las[k]==-1) continue;
                if (las[k]<las[j]) continue;
                if (k==c||k==j) continue;
                int t=k;
                if (k>c) t--;
                if (c!=j&&k>j) t--;
                s-=p[t];                 
              }
              f[c][j][s]+=a[j][c];
          }
        las[c]=i;
    }
    for (int i=0;i<m;i++)
      for (int j=0;j<m;j++) {
          if (i==j) {
              for (int k=0;k<m-1;k++) 
                for (int s=p[m-1]-1;s>=0;s--)
                  if (!(s>>k&1)) f[i][j][s]+=f[i][j][s^p[k]];
              for (int s=0;s<p[m-1];s++)
                ans[s/p[i]*p[i+1]+p[i]+s%p[i]]+=f[i][j][s];
          }
          else {
              for (int k=0;k<m-2;k++)
                for (int s=p[m-2]-1;s>=0;s--) 
                  if (!(s>>k&1)) f[i][j][s]+=f[i][j][s^p[k]];
              for (int s=0;s<p[m-2];s++)
                if (i<j) ans[s/p[j-1]*p[j+1]+s%p[i]+s%p[j-1]/p[i]*p[i+1]+p[i]+p[j]]+=f[i][j][s];
                  else ans[s/p[i-1]*p[i+1]+s%p[j]+s%p[i-1]/p[j]*p[j+1]+p[i]+p[j]]+=f[i][j][s];
           }
      }
      for (int i=(1<<m)-1;i>=0;i--) cout<<ans[i]<<' ';
      return 0;
}