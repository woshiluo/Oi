// By: Little09
// Problem: P8098 [USACO22JAN] Tests for Haybales G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8098
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e5+5;
const ll inf=100000000000000000;
ll dis[N],v[2*N],k;
int a[N];
bool used[N];
int n,m;
int cnt,nxt[2*N],t[2*N],h[2*N],d[N];
inline void add(int x,int y,int z) //x-y>=z
{
	swap(x,y);
	t[++cnt]=y;
	v[cnt]=z;
	nxt[cnt]=h[x];
	h[x]=cnt;
	d[y]++;
}
queue<int>q;
void topo(int s,int l,int r)
{
	for (int i=l;i<=r;i++) dis[i]=0,used[i]=0;
    q.push(s);
    dis[s]=0;
    for (int i=l;i<=r;i++) if (d[i]==0) q.push(i);
    while (!q.empty())
    {
    	int u=q.front();
    	q.pop();
    	for (int i=h[u];i;i=nxt[i])
    	{
    		d[t[i]]--;
    		dis[t[i]]=max(dis[t[i]],dis[u]+v[i]);
    		if (d[t[i]]==0) q.push(t[i]);
    	}
    }
}
inline int read()
{
	char C=getchar();
	int F=1,ANS=0;
	while (C<'0'||C>'9')
	{
		if (C=='-') F=-1;
		C=getchar();
	}
	while (C>='0'&&C<='9')
	{
		ANS=ANS*10+C-'0';
		C=getchar();
	}
	return F*ANS;
} 
int deth[N];
void work(int l,int r,ll qwq)
{
	deth[r]=0;
	for (int i=0;i<=cnt;i++)
	{
		nxt[i]=0,v[i]=0,t[i]=0;
	}
	for (int i=l;i<=r;i++) h[i]=0,d[i]=0;
	h[0]=0,d[0]=0;
	cnt=0;
	for (int i=r-1;i>=l;i--) deth[i]=deth[a[i]]+1;
	for (int i=l;i<r;i++)
	{
		if (deth[i]==deth[i+1])
		{
			add(i+1,i,0);
		}
	}
	for (int i=l;i<r;i++)
	{
		add(i,a[i],0);
		if (a[i]+1<=r&&deth[a[i]+1]==deth[a[i]]) 
			add(a[i]+1,i,1);
	}
	for (int i=l;i<=r;i++) add(i,0,0);
	topo(0,l,r);
	for (int i=l;i<=r;i++) dis[i]-=1ll*deth[i]*k;
	for (int i=r;i>=l;i--) dis[i]-=dis[l];
	for (int i=l;i<=r;i++) dis[i]+=qwq;
	
}
int main()
{
	n=read(),k=n+1;
	for (int i=1;i<=n;i++) a[i]=read();
	int las=1;
	ll tmp=0;
	for (int i=1;i<=n;i++)
	{
		if (a[i]==i) 
		{
			work(las,i,tmp+k+1);
			las=i+1,tmp=dis[i];
		}
	}
	printf("%lld\n",k);
	for (int i=1;i<=n;i++) printf("%lld\n",dis[i]);
	return 0;
}
