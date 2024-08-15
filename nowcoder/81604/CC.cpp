#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=1000000007;
int n,cntx[5010],cnty[5010];
LL a[5010][5010];
inline int read()
{
	int x=0,w=0;char ch=0;
	while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return w?-x:x;
}
int main()
{
    mt19937 mt(time(0));
    n=3000;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
        a[i][j]=__gcd(i,j);
    for(int t=1;t<=n;t++){
        if(mt()&1){
            int x=mt()%n+1,y=mt()%n+1;
            for(int i=1;i<=n;i++)
                a[x][i]=a[x][i]*y%mod;
            cntx[x]++;
        }else{
            int x=mt()%n+1,y=mt()%n+1;
            for(int i=1;i<=n;i++)
                a[i][x]=a[i][x]*y%mod;
            cnty[x]++;
        }
    }
    int sum=0,Max=0,MC=0,Min=1e9;
    for(int i=1;i<=n;i++){
        set<int>s;s.clear();
        for(int j=1;j<=n;j++)
        s.insert(a[i][j]);
        sum+=int(s.size());
        Max=max(Max,int(s.size()));
        Min=min(Min,int(s.size()));
        MC=max(MC,cntx[i]);
    }
    for(int i=1;i<=n;i++){
        set<int>s;s.clear();
        for(int j=1;j<=n;j++)
        s.insert(a[j][i]);
        sum+=int(s.size());
        Max=max(Max,int(s.size()));
        Min=min(Min,int(s.size()));
        MC=max(MC,cnty[i]);
    }
    cout<<sum<<' '<<Max<<' '<<Min<<' '<<MC<<'\n';
}
/*
48992 48 1 0
6655330 1208 1043 5
*/