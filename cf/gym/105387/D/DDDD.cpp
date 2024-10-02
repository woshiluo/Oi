#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int base1=233,base2=4099,mod1=998244353,mod2=1000000007;
char str[210010];
int Len,ans=0,Lp,Rp;
LL mi1[100010],mi2[100010];
struct HHH
{
    LL H1[100010],H2[100010];
    LL calc1(int l,int r){
        return ((H1[r]-H1[l-1]*mi1[r-l+1])%mod1+mod1)%mod1;
    }
    LL calc2(int l,int r){
        return ((H2[r]-H2[l-1]*mi2[r-l+1])%mod2+mod2)%mod2;
    }
}A,B;
int check(int l,int r)
{
    return (A.calc1(l,r)==B.calc1(Len-r+1,Len-l+1)&&A.calc2(l,r)==B.calc2(Len-r+1,Len-l+1));
}
unordered_map<LL,int>mp;
int check(int M)
{
    mp.clear();
    for(int i=1;i+M-1<=Len;i++)
        mp[A.calc1(i,i+M-1)*mod2+A.calc2(i,i+M-1)]=i;
    for(int i=1;i+M-1<=Len;i++)
    if(mp.count(B.calc1(i,i+M-1)*mod2+B.calc2(i,i+M-1)))
        return mp[B.calc1(i,i+M-1)*mod2+B.calc2(i,i+M-1)];
    return 0;
}
int main()
{
// #ifdef woshiluo
// 	freopen( "d.in", "r", stdin );
// 	freopen( "d.out", "w", stdout );
// #endif
    scanf("%s",str+1);
    Len=strlen(str+1);
    mi1[0]=mi2[0]=1;
    for(int i=1;i<=Len;i++){
        mi1[i]=mi1[i-1]*base1%mod1;
        mi2[i]=mi2[i-1]*base2%mod2;
    }
    for(int i=1;i<=Len;i++){
        A.H1[i]=(A.H1[i-1]*base1+str[i])%mod1;
        A.H2[i]=(A.H2[i-1]*base2+str[i])%mod2;
    }
    reverse(str+1,str+1+Len);
    for(int i=1;i<=Len;i++){
        if(str[i]=='A')str[i]='T';
        else if(str[i]=='T')str[i]='A';
        else if(str[i]=='C')str[i]='G';
        else str[i]='C';
        B.H1[i]=(B.H1[i-1]*base1+str[i])%mod1;
        B.H2[i]=(B.H2[i-1]*base2+str[i])%mod2;
    }
    reverse(str+1,str+1+Len);
    for(int i=1;i<=Len;i++){
        if(str[i]=='A')str[i]='T';
        else if(str[i]=='T')str[i]='A';
        else if(str[i]=='C')str[i]='G';
        else str[i]='C';
    }
    int L=1,R=Len,M,T=0,POS=0;
    while(L<=R){
        M=(L+R)>>1;
        int temp=check(M);
        if(temp)POS=temp,T=M,L=M+1;
        else R=M-1;
    }
    cout<<T<<'\n';
    for(int i=POS;i<=POS+T-1;i++)
        printf("%c",str[i]);
    cout<<endl;
}
