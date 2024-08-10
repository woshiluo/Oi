#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,b[2010],a[2010],f[2010][3][3],ans,sum1,sum2;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int check(int x,int y)
{
    if(x==y)return 0;
    if(x==1&&y==0||x==2&&y==1||x==0&&y==2)
        return 1;
    return -1;
}
void dfs(int x,int last,int tot)
{
    if(x>n)return ans=max(ans,tot),void();
    for(int i=0;i<3;i++){
        int temp=check(i,a[x]);
        if(temp==-1||i==last)continue;
        dfs(x+1,i,tot+temp);
    }
}
void calc(int x)
{
    if(x>n){
        memset(f,-0x3f,sizeof(int)*(n+5)*9);
        f[0][0][0]=f[0][0][1]=f[0][1][1]=f[0][1][2]=f[0][2][2]=f[0][2][0]=0;
        for(int i=1;i<=n;i++)
        for(int j=0;j<=2;j++){
            int temp=check(j,a[i]);
            if(temp==-1)continue;
            for(int k=0;k<=2;k++)
            if(k^j)
                f[i][a[i]][j]=max(f[i][a[i]][j],f[i-1][a[i-1]][k]+temp);
        }
        ans=0;
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            ans=max(ans,f[n][i][j]);
        sum1+=ans;
        ans=0;
        dfs(1,-1,0);
        sum2+=ans;
        return;
    }
    if(b[x]!=-1)a[x]=b[x],calc(x+1);
    else{
        a[x]=0;calc(x+1);
        a[x]=1;calc(x+1);
        a[x]=2;calc(x+1);
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();
        for(int i=1;i<=n;i++)
            b[i]=read();
        sum1=sum2=0;
        calc(1);
        cout<<sum1<<' '<<sum2<<'\n';
    }
}
/*
5
4
-1 0 1 2
7
0 -1 1 2 -1 1 0
12
0 0 -1 -1 1 1 -1 -1 2 2 -1 -1
10
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1

11
49
5648
443085
*/