#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int mod=998244353;
int ss[500010],vis[6000010];
const int S=63;
int n,f[400010][64],g[400010][64];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void xxs()
{
    for(int i=2;i<=6000000;i++){
        if(!vis[i])ss[++ss[0]]=i;
        for(int j=1;i*ss[j]<=6000000;j++){
            vis[i*ss[j]]=1;
            if(i%ss[j]==0)break;
        }
    }
}
void calc()
{
    int Min=1e9,state=0;
    for(int i=0;i<(1<<n);i++){
        int delta=0;
        for(int j=1;j<=n;j++)
        if(i>>(j-1)&1)
            delta+=ss[j];
        else delta-=ss[j];
        delta=abs(delta);
        if(delta<Min){
            Min=delta;state=i;
        }
    }
    for(int i=1;i<=n;i++)
    if(state>>(i-1)&1)
        printf("A");
    else printf("B");
    printf("\n");
}
void print(int state)
{
    for(int i=1;i<=6;i++)
    if(state>>(i-1)&1)
        printf("A");
    else printf("B");
}

void getg(int i,int j);

void getf(int i,int j)
{
    // cout<<"F"<<' '<<i<<' '<<j<<'\n';
    if(i==n-5){
        print(j);
        return;
    }
    int j2=j>>1,val=f[i][j];
    if(j&1)val-=ss[i];
    else val+=ss[i];
    printf((j&1)?"A":"B");

    if(f[i+1][j2]==val){
        getf(i+1,j2);
        return;
    }
    if(g[i+1][j2]==val){
        getg(i+1,j2);
        return;
    }
    j2+=32;
    if(f[i+1][j2]==val){
        getf(i+1,j2);
        return;
    }
    if(g[i+1][j2]==val){
        getg(i+1,j2);
        return;
    }
}
void getg(int i,int j)
{
    if(i==n-5){
        print(j);
        return;
    }
    int j2=j>>1,val=g[i][j];
    if(j&1)val-=ss[i];
    else val+=ss[i];
    printf((j&1)?"A":"B");
    if(f[i+1][j2]==val){
        getf(i+1,j2);
        return;
    }
    if(g[i+1][j2]==val){
        getg(i+1,j2);
        return;
    }
    j2+=32;
    if(f[i+1][j2]==val){
        getf(i+1,j2);
        return;
    }
    if(g[i+1][j2]==val){
        getg(i+1,j2);
        return;
    }
}
int main()
{
    xxs();
    int T=read();
    while(T --> 0){
        n=read();
        if(n<6){
            calc();
            continue;
        }
        memset(f,0x3f,sizeof(int)*(n+5)*(S+1));
        memset(g,-0x3f,sizeof(int)*(n+5)*(S+1));
        for(int i=0;i<=S;i++){
            int delta=0;
            for(int j=1;j<=6;j++){
                if(i>>(j-1)&1)
                    delta+=ss[n-6+j];
                else delta-=ss[n-6+j];
            }
            if(delta<0)g[n-5][i]=delta;
            else f[n-5][i]=delta;
        }
        for(int i=n-5;i;i--){
            for(int j=0;j<=S;j++){
                int j2=((j<<1)&S),temp=f[i][j]-ss[i-1];
                if(temp<0)g[i-1][j2]=max(g[i-1][j2],temp);
                else f[i-1][j2]=min(f[i-1][j2],temp);
                j2=((j<<1)&S);temp=g[i][j]-ss[i-1];
                if(temp<0)g[i-1][j2]=max(g[i-1][j2],temp);
                else f[i-1][j2]=min(f[i-1][j2],temp);;
                j2=((j<<1)&S)|1;temp=f[i][j]+ss[i-1];
                if(temp<0)g[i-1][j2]=max(g[i-1][j2],temp);
                else f[i-1][j2]=min(f[i-1][j2],temp);
                j2=((j<<1)&S)|1;temp=g[i][j]+ss[i-1];
                if(temp<0)g[i-1][j2]=max(g[i-1][j2],temp);
                else f[i-1][j2]=min(f[i-1][j2],temp);
            }
        }
        int ans=1e9;
        for(int i=0;i<=S;i++)
            ans=min(ans,min(f[1][i],-g[1][i]));
        for(int i=0;i<=S;i++){
            if(f[1][i]==ans){
                getf(1,i);
                break;
            }
            if(-g[1][i]==ans){
                getg(1,i);
                break;
            }
        }
        printf("\n");
    }
}