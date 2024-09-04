#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,m,f[3010],g[3010],val[20];
inline LL read()
{
    LL x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int calc(int j)
{
    int temp=0;
    while(f[j]*10>temp*j)temp++;
    return val[temp]*j;
}
int main()
{
    int T=read();
    while(T --> 0){
        for(int i=1;i<=10;i++)
            val[i]=read();
        memset(f,-0x3f,sizeof f);
        memset(g,-0x3f,sizeof g);
        f[0]=0;g[0]=0;
        n=read();m=read();
        for(int i=1;i<=n;i++){
            int B=read(),A=read();
            for(int j=0;j+B<=m;j++)
                f[j+B]=max(f[j+B],f[j]+A);
        }
        for(int i=0;i<=m;i++)
        for(int j=1;i+j<=m;j++)
            g[i+j]=max(g[i+j],g[i]+calc(j));
        cout<<g[m]<<'\n';
    }
}