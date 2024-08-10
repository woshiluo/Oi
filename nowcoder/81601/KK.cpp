#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,K,KKK,a[5010],MINst[5010],MAXst[5010],MINTOP,MAXTOP;
int f[5010][5010],g[5010][5010],h[5010][5010],Max[5010][15],Min[5010][15],Log[5010];
inline int read(int x=0)
{scanf("%d",&x);return x;}
void prepare()
{
    Log[0]=-1;
    for(int i=1;i<=n;i++){
        Log[i]=Log[i>>1]+1;
        Max[i][0]=Min[i][0]=a[i];
    }
    for(int t=1;t<=Log[n];t++){
        for(int i=1;i+(1<<t)-1<=n;i++){
            Min[i][t]=min(Min[i][t-1],Min[i+(1<<(t-1))][t-1]);
            Max[i][t]=max(Max[i][t-1],Max[i+(1<<(t-1))][t-1]);
        }
    }
}
int ask(int l,int r)
{
    int t=Log[r-l+1];
    return max(Max[l][t],Max[r-(1<<t)+1][t])-min(Min[l][t],Min[r-(1<<t)+1][t]);
}
int main()
{
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    n=read();
    for(int i=1;i<=n;i++)
       a[i]=read();
//     n=20;mt19937 mt(233);
//     for(int i=1;i<=n;i++)
//         a[i]=mt()%100000+1;
    prepare();
    memset(h,0x3f,sizeof h);
    for(int K=0;K<n;K++){
        for(int i=1;i<=n;i++){
            for(int j=0;j<min(10,i);j++){
                int temp=f[K][j]+ask(j+1,i);
                 if(temp<f[K+1][i]){
                    g[K+1][i]=j;
                    f[K+1][i]=temp;
                 }
            }
            for(int j=g[K][i];j<i;j++){
                int temp=f[K][j]+ask(j+1,i);
                 if(temp<f[K+1][i]){
                    g[K+1][i]=j;
                    f[K+1][i]=temp;
                 }
            }
        }
    }
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=n;j++)
//             cout<<g[i][j]<<','<<h[i][j]<<" \n"[j==n];
//     }
    for(int i=1;i<=n;i++)
        cout<<f[i][n]<<'\n';
}
