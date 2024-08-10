#include<bits/stdc++.h>
#define LL long long
using namespace std;
int n,m,f[1000010][26];
char S[1000010],T[1000010];
int posl[1000010],posr[1000010];
LL ans=0,g[1000010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
void calc()
{
    int Lp=1,Rp=n;
    ans++;
    g[Lp-1]=1;
    for(int i=0;i<26;i++)f[Lp-1][i]=-1;
    for(int i=Lp;i<=Rp;i++){
        memcpy(f[i],f[i-1],sizeof f[i]);
        for(int j=0;j<26;j++)
        if(f[i][j]!=-1)
            (g[i]+=g[f[i][j]])%=1000000007;
        g[i]++;
        f[i][S[i]-'a']=i;
    }
    for(int i=0;i<26;i++){
        if(f[Rp][i]!=-1)
            (ans+=g[f[Rp][i]])%=1000000007;
    }
}
int main()
{
    //n=read();
    scanf("%s",S+1);
    n=strlen(S+1);
    calc();
    cout<<ans<<'\n';
}
/*
9 2
abcabacba
be
*/