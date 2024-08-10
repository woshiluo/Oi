#include<bits/stdc++.h>
#define Graph(x)for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
#define LL long long
const int mod=998244353;
using namespace std;
int n,m,last[10010],num,du[10010];
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
void tarjan(int x)
{

}
int main()
{
    int T=read();
    while(T --> 0){
        n=read();m=read();num=1;
        memset(last,0,sizeof(int)*(n+5));
        memset(du,0,sizeof(int)*(n+5));
        for(int i=1;i<=m;i++){
            int x=read(),y=read();
            add(x,y);add(y,x);
            du[x]++;du[y]++;
        }

    }
}