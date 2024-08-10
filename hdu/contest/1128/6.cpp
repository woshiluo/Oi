#include<bits/stdc++.h>
#define LL long long
const int mod=998244353;
using namespace std;
int vis[21][21][21];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int dfs(int x,int y,int z)
{
    if(x>y)swap(x,y);
    if(y>z)swap(y,z);
    if(x>y)swap(x,y);
    if(vis[x][y][z]!=-1)
        return vis[x][y][z];
    for(int i=1;i<x;i++){
        if(!dfs(i,x-i,y))
            return vis[x][y][z]=1;
        if(!dfs(i,x-i,z))
            return vis[x][y][z]=1;
    }
    for(int i=1;i<y;i++){
        if(!dfs(i,y-i,x))
            return vis[x][y][z]=1;
        if(!dfs(i,y-i,z))
            return vis[x][y][z]=1;
    }
    for(int i=1;i<z;i++){
        if(!dfs(i,z-i,y))
            return vis[x][y][z]=1;
        if(!dfs(i,z-i,x))
            return vis[x][y][z]=1;
    }
    return vis[x][y][z]=0;
}
int gcd(int x,int y)
{return y?gcd(y,x%y):x;}
int main()
{
    for(int x=1;x<=10;x++)
    for(int y=1;y<=10;y++)
    for(int z=1;z<=10;z++){
        memset(vis,-1,sizeof vis);
        int temp=0,flag=0;
        if(dfs(x,y,z))temp=1;
        int xx,yy,zz,G=gcd(gcd(x,y),z);
        xx=x/G;yy=y/G;zz=z/G;
        if((xx&1)+(yy&1)+(zz&1)==3){

        }else flag=1;
        cout<<x<<' '<<y<<' '<<z<<'\n';
        cout<<temp<<' '<<flag<<'\n';
        assert(temp==flag);
    }
    cout<<"OK\n";
}