#include<bits/stdc++.h>
#define LL int
#define Graph(x)for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
using namespace std;
const LL inf=0x3f3f3f3f;
int n,m,S,T,last[200010],_last[200010],num=1;
int dep[200010],que[200010],tou,wei,fa[200010],A[200010],B[200010],vis[200010];
LL ans;
struct EDGE
{int ver,next;LL len;}edge[2000010];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
void add(int X,int Y,LL Z)
{edge[++num]=(EDGE){Y,last[X],Z};last[X]=num;}
bool bfs()
{
	memcpy(last,_last,sizeof(int)*(n*2+5));
	memset(dep,0,sizeof(int)*(n*2+5));
	dep[que[tou=wei=1]=S]=1;
	while(tou<=wei){
		int x=que[tou++];
		Graph(x){
			if(dep[y]||!edge[i].len)continue;
			dep[que[++wei]=y]=dep[x]+1;
			if(y==T)return 1;
		}
	}
    return 0;
}
LL dinic(int x,LL flow)
{
	if(x==T)return flow;
	LL temp=flow,liu;
	for(int &i=last[x],y;i;i=edge[i].next)
	if(dep[y=edge[i].ver]==dep[x]+1&&edge[i].len){
		liu=dinic(y,min(temp,edge[i].len));
		if(!liu)dep[y]=0;
		temp-=liu;
		edge[i].len-=liu;
		edge[i^1].len+=liu;
		if(!temp)return flow;
	}
	return flow-temp;
}
int getfa(int x)
{return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void merge(int x,int y)
{
    x=getfa(x);
    y=getfa(y);
    fa[x]=y;
}
void dfs(int x,int flag)
{
    if(vis[x])return;
    vis[x]=1;
    Graph(x){
        if(flag==edge[i].len&&x<=n)continue;
        if(x>n&&flag!=edge[i].len)continue;
        if(y==S||y==T||vis[y])continue;
        dfs(y,1-flag);
    }
}
int main()
{
    int t=read();
    while(t --> 0){
        n=read();m=read();
        memset(last,0,sizeof(int)*(n*2+5));
        num=1;
        S=n+n+1;T=S+1;
        iota(fa+1,fa+1+n+n,1);
        for(int i=1;i<=m;i++){
            int x=read(),y=read();
            add(x,n+y,1);add(n+y,x,0);
            merge(x,y+n);
        }
        for(int i=1;i<=n;i++){
            add(S,i,1);add(i,S,0);
            add(T,i+n,0);add(i+n,T,1);
            A[i+n]=B[i+n]=0;
            A[i]=B[i]=0;
        }
        memcpy(_last,last,sizeof(int)*(n*2+5));
        ans=0;
        LL temp=0;
	    while(bfs())
		    while((temp=dinic(S,inf)))
			    ans+=temp;
        long long Lt=0,Rt=0;
        Graph(S)if(edge[i].len)dfs(y,0);
        for(int i=1;i<=n;i++){
            if(vis[i])Lt++;
            vis[i]=vis[i+n]=0;
        }
        Graph(T)if(!edge[i].len)dfs(y,0);     
        for(int i=1;i<=n;i++){
            if(vis[i+n])Rt++;
            vis[i+n]=vis[i]=0;
        }
        printf("%lld\n",Lt*Rt);
    }
}
/*
1
5 4
1 5
1 2
3 2
3 4
*/