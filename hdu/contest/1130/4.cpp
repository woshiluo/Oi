#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,r1,r2,num,last[100010],f[100010],ans;
struct EDGE
{int ver,next;}edge[200010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void add(int X,int Y)
{edge[++num]=(EDGE){Y,last[X]};last[X]=num;}
void dfs(int x,int F)
{
    f[x]=0;
    for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver){
        if(y==F)continue;
        dfs(y,x);
        ans=max(ans,f[x]+f[y]+1);
        f[x]=max(f[x],f[y]+1);
    }
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();read();r1=read();r2=read();
        memset(last,num=0,sizeof(int)*(n+5));
        for(int i=1;i<n;i++){
            int x=read(),y=read();
            add(x,y);add(y,x);
        }
        ans=0;
        dfs(1,0);
        if(min(r2,ans)>2*r1)
            printf("General_Kangaroo\n");
        else printf("Kangaroo_Splay\n");
    }
}