#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int mod=998244353;
int n,m,a[10010],AND,f[2][10010];
int Lp[10010],Rp[100010];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(i==1)AND=a[i];
        else AND&=a[i];
    }
    f[0][0]=1;
    // cout<<AND<<'\n';
    memset(Lp,0x3f,sizeof Lp);
    memset(Rp,-0x3f,sizeof Rp);
    for(int i=1;i<=n;i++){
        int temp=a[i];
        for(int j=i;j;j--){
            temp&=a[j];
            if(temp==AND){
                Lp[i]=min(Lp[i],j);
                Rp[i]=max(Rp[i],j);
            }
        }
        // cout<<i<<' '<<Lp[i]<<' '<<Rp[i]<<'\n';
    }
    int A=0,B=1;
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++)
            (f[A][i]+=f[A][i-1])%=mod;
        for(int i=1;i<=n;i++)
        if(Lp[i]<=Rp[i]){
            if(Lp[i]>=2)
                f[B][i]=(f[A][Rp[i]-1]-f[A][Lp[i]-2])%mod;
            else f[B][i]=f[A][Rp[i]-1];
        }
        swap(A,B);
        memset(f[B],0,sizeof f[B]);
    }
    cout<<(f[A][n]+mod)%mod<<'\n';
}