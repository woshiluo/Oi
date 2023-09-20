#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int n,m,a[N],lens,lent;
int stk[N],top;
char s[N],t[N];
struct node{
	int x,y;
	bool operator<(const node &B)const{
		if(x^B.x) return x<B.x;
		return y<B.y;
	}
}S[N];

bool ck(int i,int j,int k)
{
	return (S[j].y-S[i].y)*(S[k].x-S[j].x)<=(S[k].y-S[j].y)*(S[j].x-S[i].x);
}
void work()//维护上凸壳
{
	for(int i=1;i<=n;i++)
	{
		while(top>1 && ck(stk[top-1],stk[top],i)) top--;
		stk[++top]=i;
	}
} 
int get(int a,int b)
{
	int l=1,r=top-1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if((S[stk[mid+1]].y-S[stk[mid]].y)*b  <= -a*(S[stk[mid+1]].x-S[stk[mid]].x))
			r=mid;
		else l=mid+1;
	}
	return stk[r];
}
signed main()
{
	freopen( "t1.in", "r", stdin );
	scanf("%s",s+1);
	lens=strlen(s+1);
	for(int i=1;i<=lens;i++)
		a[i]=a[i-1]+(s[i]=='1');
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int l,r;
		scanf("%lld%lld",&l,&r);
		int s1=a[r]-a[l-1];
		int s0=(r-l+1)-s1;
		S[i].x=s1,S[i].y=s0;
	}
	sort(S+1,S+1+n);
	work();
	S[n+1].x=S[n].x+1,S[n+1].y=-2*n;
	stk[++top]=n+1;
	scanf("%s",t+1);
	lent=strlen(t+1);
	for(int i=1;i<=lent;i++)
		a[i]=a[i-1]+(t[i]=='1');
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%lld%lld",&l,&r);
		int c1=a[r]-a[l-1];
		int c0=(r-l+1)-c1;
		int j=get(c0+1,c1+1);
		printf("%lld\n",(c0+1)*S[j].x+(c1+1)*S[j].y+r-l+2);
	}
	
	return 0;
}
