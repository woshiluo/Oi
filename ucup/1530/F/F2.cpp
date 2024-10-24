#include<bits/stdc++.h>
using namespace std;
int n,L,R,a[110];
long long f[110][110],g[110][110],sum[110];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>L>>R;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++){
        sum[i]=sum[i-1]+a[i];
        f[i][i]=0;
    }
    for(int len=2;len<=n;len++){
        
        for(int l=1;l+len-1<=n;l++){
            int r=l+len-1;
            memset(g,0x3f,sizeof g);
            for(int )
        }
    }
    
    if(f[1][n]>1e15)f[1][n]=0;
    cout<<f[1][n]<<endl;
}