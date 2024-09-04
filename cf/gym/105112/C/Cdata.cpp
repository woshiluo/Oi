#include<bits/stdc++.h>
#define LL long long
using namespace std;
int nn,n,q,id[500010],vis[500010],vis2[500010];
char str[10];
vector<int>POS,POS2;
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
LL exgcd(LL N,LL M,LL&X,LL&Y)
{
    if(!M){X=1;Y=0;return N;}
    LL gCd=exgcd(M,N%M,Y,X);
    Y-=N/M*X;
    return gCd;
}
LL Inv(LL N,LL P,LL k1=0,LL k2=0)
{
    exgcd(N,P,k1,k2);
    return(k1%P+P)%P;
}
int calc(LL p)
{return (n+p-1)%n+1;}
int calcdis(LL x,LL y)
{
    if(x<=y)return y-x;
    return y+n-x;
}
int main()
{
    mt19937 mt(time(0));
    n=12;q=6;
    cout<<n<<' '<<q<<'\n';
    while(q --> 0){
        int abc=mt()%3;
        if(abc==1)cout<<"? ";
        if(abc==0)cout<<"+ ";
        if(abc==2)cout<<"* ";
        cout<<mt()%n+1<<'\n';
    }
}