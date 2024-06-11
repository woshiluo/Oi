
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef double db; 
typedef long long ll;
typedef unsigned long long ull;
const int N=1000010;
const int LOGN=28;
const ll  TMD=0;
const ll  INF=2147483647;
int  T,n;
ll   Sl[N],Sr[N],IDl[N],IDr[N];
char s[N];

int findpre(int x)
{
	int L=0,R=n+1,M;
	while(L+1!=R)
	{
		M=(L+R)>>1;
		if(Sr[M]<x) L=M;
		else R=M; 
	}
	return R;
}

int findsuf(int x)
{
	int L=0,R=n+1,M;
	while(L+1!=R)
	{
		M=(L+R)>>1;
		if(Sl[n]-Sl[M-1]<x) R=M;
		else L=M; 
	}
	return L;
}

int main()
{
	freopen( "d.in" ,"r", stdin );
	freopen( "d.ans", "w", stdout );
	scanf("%d",&T);
	while(T--)
	{
    	        scanf("%d%s",&n,s);
		for(int i=1;i<=n;i++) 
		{
	  	  Sr[i]=Sr[i-1]+(s[i-1]=='>');
	  	  Sl[i]=Sl[i-1]+(s[i-1]=='<');
 		  IDr[i]=IDr[i-1]+i*(s[i-1]=='>'); 	
 		  IDl[i]=IDl[i-1]+i*(s[i-1]=='<'); 	
		}		
		for(int i=1;i<=n;i++)
		{
			if(s[i-1]=='>')
			{
				if(Sr[i]>Sl[n]-Sl[i])
				{
					int p=findpre(Sr[i]-(Sl[n]-Sl[i]));
					printf("%lld ",2*((IDl[n]-IDl[i])-(IDr[i]-IDr[p-1]))+i+(n+1));
				}
				else
				{
					int p=findsuf((Sl[n]-Sl[i])-Sr[i]+1);
					printf("%lld ",2*((IDl[p]-IDl[i])-(IDr[i]-IDr[0]))+i);
				}
			}
			else
			{
				if(Sr[i]>=Sl[n]-Sl[i-1])
				{
					int p=findpre(Sr[i]-(Sl[n]-Sl[i-1])+1);
					printf("%lld ",2*((IDl[n]-IDl[i-1])-(IDr[i]-IDr[p-1]))-i+(n+1));
				}
				else
				{
					int p=findsuf((Sl[n]-Sl[i-1])-Sr[i]);
					printf("%lld ",2*((IDl[p]-IDl[i-1])-(IDr[i]-IDr[0]))-i);
				}
			}
		}
		printf("\n");
	}
	
	return 0;
}
