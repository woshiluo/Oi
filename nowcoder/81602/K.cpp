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
    int Lp=posl[m],Rp=posr[m];
    if(Lp>=Rp)
        return;
    ans++;
    Lp++;Rp--;
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
const int base1=233,base2=4099;
const int mod1=998244353,mod2=1004535809;
LL h1[1000010],h2[1000100],m1[1000010],m2[1000100];
LL hh1[1000010],hh2[1000010];
int check(int Len)
{
    if(hh1[Len]!=((h1[m]-h1[m-Len]*m1[Len])%mod1+mod1)%mod1)
        return 0;
    if(hh2[Len]!=((h2[m]-h2[m-Len]*m2[Len])%mod2+mod2)%mod2)
        return 0;
    if(posl[m]>=posr[m-Len])
        return 0;
    return 1;
}
void calc2()
{
    for(int i=1;i<=m;i++)
    if(check(i))
        ans++;
}
void prepare()
{
    m1[0]=m2[0]=1;
    for(int i=1;i<=m;i++){
        h1[i]=h1[i-1]*base1%mod1+T[i];
        h2[i]=h2[i-1]*base2%mod2+T[i];
        m1[i]=m1[i-1]*base1%mod1;
        m2[i]=m2[i-1]*base2%mod2;
        hh1[i]=hh1[i-1]*base1%mod1+T[m-i+1];
        hh2[i]=hh2[i-1]*base2%mod2+T[m-i+1];
    }
    int Lp=1,Rp=n;
    for(int i=1;i<=m;i++){
        while(Lp<=n&&S[Lp]!=T[i])Lp++;
        posl[i]=Lp++;
    }
    for(int i=1;i<=m;i++){
        while(Rp>0&&S[Rp]!=T[i])Rp--;
        posr[i]=Rp--;
    }
    posl[0]=0;
    posr[0]=n+1;
}
int main()
{
    n=read();m=read();
    scanf("%s%s",S+1,T+1);
    prepare();
    calc();
    if(posl[m]<=n)
        calc2();
    cout<<ans%1000000007<<'\n';
}
/*
9 2
abcabacba
be
*/