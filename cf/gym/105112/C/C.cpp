#include<bits/stdc++.h>
#define LL long long
using namespace std;
int nn,n,q,id[500010],vis[500010],vis2[500010],vis3[500010];
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
    x=calc(x);y=calc(y);
    if(x<=y)return y-x;
    return y+n-x;
}
int main()
{
    nn=n=read();q=read();
    for(int i=1;i<=n;i++){
        id[i]=i;
        POS.emplace_back(i);
    }
    LL K=1,B=0;
    while(q --> 0){
        scanf("%s",str);
        if(*str=='?'){
            int pos=read();
            // cout<<pos<<' '<<Inv(K,n)<<'\n';
            pos=Inv(K,n)*((pos-B)%n+n)%n;
            printf("%d\n",id[calc(pos)]);
        }
        if(*str=='+')B=(B+read())%n;
        // cout<<"x*"<<K<<"+"<<B<<'\n';
        if(*str=='*'){
            LL temp=read();
            LL k1=0,k2=0,G=exgcd(nn,temp,k1,k2);
            if(G==1){
                K=K*temp%n;
                B=B*temp%n;
            }else{
                nn/=G;
                for(int x:POS)vis[x]=vis3[x]=0,vis2[x]=-1;
                POS2.clear();
                for(int x:POS){
                    int ix=x;
                    x=((K*x+B)%n+n)%n;
                    x=calc(x);
                    LL y=calc(x*temp);
                    // cout<<ix<<" -> "<<x<<" -> "<<y<<"\n";
                    if(!vis[y])vis[y]=ix,vis3[y]=x;
                    else{
                        if(calcdis(x,y)<calcdis(vis3[y],y))
                            vis[y]=ix,vis3[y]=x;
                    }
                }
                // for(int i=1;i<=12;i++)
                //     cout<<vis[i]<<" \n"[i==12];
                for(int x:POS){
                    int ix=x;
                    x=((K*x+B)%n+n)%n;
                    x=calc(x);
                    LL y=calc(x*temp);
                    if(vis[y]==ix){
                        vis2[y]=id[ix];
                        POS2.push_back(y);
                    }
                    id[ix]=-1;
                }
                for(int x:POS2)
                    id[x]=vis2[x];
                K=1;B=0;
                swap(POS,POS2);
            }
        }
    }
}
/*
12 5
* 9
+ 1
* 11
+ 7
? 2

-1
*//*
12 5
+ 8
? 12
* 3
* 3
? 3


11
*/