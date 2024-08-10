#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int n,b[2010];
LL f[2010][2010][3][3],g[2010][3][3],ans;
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
int main()
{
    int T=read();
    while(T --> 0){
        memset(f,0,sizeof f);
        memset(g,0,sizeof g);
        n=read();
        for(int i=1;i<=n;i++)b[i]=read();
        {
            int La=b[1],Ra=b[1];
            if(b[1]==-1)La=0,Ra=2;
            for(int na=La;na<=Ra;na++)
            for(int i=0;i<=2;i++){
                int temp=check(i,na);
                if(temp==-1)continue;
                f[1][temp][na][i]++;
            }
        }
        for(int i=1;i<n;i++)
        for(int j=0;j<=i;j++){
            int La=b[i+1],Ra=b[i+1],lLa=b[i],lRa=b[i];
            if(b[i+1]==-1)La=0,Ra=2;
            if(b[i]==-1)lLa=0,lRa=2;
            for(int na=La;na<=Ra;na++)
            for(int me=0;me<=2;me++){
                int temp=check(me,na);
                if(temp==-1)continue;
                for(int la=lLa;la<=lRa;la++)
                for(int lm=0;lm<=2;lm++)
                if(check(lm,la)!=-1)
                    (f[i+1][j+temp][na][me]+=f[i][j][la][lm])%=mod;
            }
        }
        // for(int i=1;i<=n;i++)for(int j=0;j<=i;j++){cout<<"<"<<i<<','<<j<<">\n";for(int x=0;x<=2;x++)for(int y=0;y<=2;y++)cout<<f[i][j][x][y]<<" ";cout<<endl;}
        ans=0;
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            g[0][i][j]=f[n][0][i][j];
        for(int k=1;k<=n;k++)
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            g[k][i][j]=(g[k-1][i][j]+f[n][k][i][j])%mod;
        }
        for(int k=1;k<=n;k++)
        for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            (ans+=(f[n][k][i][j]-(g[n][i][j]-g[k][i][j]))*k)%=mod;
        cout<<(ans+mod)%mod<<'\n';
    }
}
/*
1 2
0 0
*//*
5
5
0 0 2 1 1
4
-1 0 1 2
7
0 -1 1 2 -1 1 0
12
0 0 -1 -1 1 1 -1 -1 2 2 -1 -1
10
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1


*/