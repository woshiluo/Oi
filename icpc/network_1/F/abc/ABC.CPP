#include<bits/stdc++.h>
using namespace std;
int n,id[200010],a[200010],fa[1000010];
vector<int>G[1000010];
long long ans=0;
set<int>s;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int cmp(int n1,int n2)
{return a[n1]>a[n2];}
int getfa(int x)
{return fa[x]==x?x:fa[x]=getfa(fa[x]);}
int merge(int x,int y)
{
    x=getfa(x);
    y=getfa(y);
    if(x==y)ans++;
    fa[x]=y;
}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();ans=0;
        for(int i=0;i<=n+1;i++)G[i].clear();
        for(int i=0;i<=n+1;i++)fa[i]=i;
        for(int i=1;i<=n;i++){
            int x=read(),y=read();
            G[x-1].emplace_back(y+1);
            G[y+1].emplace_back(x-1);
            merge(x-1,y+1);
        }
        if(ans||getfa(0)!=getfa(n+1))
        printf("0\n");
        else printf("1\n");
    }
}