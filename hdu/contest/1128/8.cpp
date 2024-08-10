#include<bits/stdc++.h>
#define LL long long
#define Graph(x)for(int i=last[x],y=edge[i].ver;i;i=edge[i].next,y=edge[i].ver)
using namespace std;
const LL inf=0x3f3f3f3f3f3f3f3f;
int n,m,S,T,last[2010],_last[2010],num=1;
int dep[2010],que[2010],tou,wei,vis[1010];
LL ans,sum[1010][1010],ANS,Sum[2][1010];
vector<pair<int,int>>G[2][1010];
struct EDGE
{int ver,next;LL len;}edge[20000010];
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
	memcpy(last,_last,sizeof last);
	memset(dep,0,sizeof dep);
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
void dfs(int x,int F,int iD)
{
    Sum[iD][x]=0;
    for(auto p:G[iD][x]){
        int y=p.first,z=p.second;
        if(vis[x]&&vis[y]){
            Sum[iD][x]+=z;
            sum[x][y]+=z;
            ANS+=z;
        }
        if(y==F)continue;
        dfs(y,x,iD);
    }
}
int main()
{
    int DUOCE=read();
    while(DUOCE --> 0){
        n=read();m=read();
        for(int i=1;i<=n;i++){
            G[0][i].clear(),G[1][i].clear();
            memset(sum[i],0,sizeof(LL)*(n+5));
        }
        S=n+n+1;T=S+1;ANS=ans=0;
        num=1;
        memset(vis,0,sizeof vis);
        memset(last,0,sizeof last);
        memset(_last,0,sizeof _last);
        for(int i=1;i<=m;i++)
            vis[read()]=1;
        for(int t=0;t<2;t++)
        for(int i=1;i<n;i++){
            int x=read(),y=read(),z=read();
            G[t][x].push_back({y,z});
            G[t][y].push_back({x,z});
        }
        dfs(1,0,0);
        dfs(1,0,1);
        for(int x=1;x<=n;x++)
        for(int y=1;y<=n;y++)
        if(x^y){
            if(!sum[x][y])continue;
            add(x,y+n,sum[x][y]);
            add(y+n,x,0);
        }
        for(int i=1;i<=n;i++){
            add(S,i,Sum[0][i]);
            add(i,S,0);
            add(i+n,T,Sum[1][i]);
            add(T,i+n,0);
        }
        LL temp=0;
        memcpy(_last,last,sizeof last);
        while(bfs())
            while((temp=dinic(S,inf)))
                ans+=temp;
        cout<<(ANS-ans)/2<<endl;
    }
}

/*
4
4 3
1 2 3
1 2 1
2 3 2
2 4 1
2 3 5
2 4 1
4 1 1
4 3
1 2 3
1 2 2
2 3 1
2 4 1
2 3 2
2 4 1
4 1 1
4 3
1 2 3
1 2 1
2 3 2
2 4 1
2 3 5
2 4 1
4 1 1
4 3
1 2 3
1 2 2
2 3 1
2 4 1
2 3 2
2 4 1
4 1 1
*/