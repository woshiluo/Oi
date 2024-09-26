#include<bits/stdc++.h>
using namespace std;
int n,f[1000010][4];
char s1[1000010],s2[1000010];
int main()
{
    cin>>n;
    scanf("%s",s1+1);
    scanf("%s",s2+1);
    memset(f,0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;i++)
        s1[i]-='a',s2[i]-='a';
    for(int i=1;i<=n;++i){
    if(s1[i]==s2[i]){
        f[i][0]=min(min(f[i-1][0],f[i-1][1]),min(f[i-1][2],f[i-1][3]));
    }if(s1[i]==(25-s2[i])){
        f[i][1]=min(min(f[i-1][3],f[i-1][1]),min(f[i-1][2],f[i-1][0])+1);
    }if(s1[i]==(13+s2[i])%26){
        f[i][2]=min(min(f[i-1][1],f[i-1][0])+1,min(f[i-1][2],f[i-1][3]));
    }if(s1[i]==(38-s2[i])%26){
        f[i][3]=min(min(f[i-1][3],f[i-1][1]+1),min(f[i-1][2]+1,f[i-1][0]+2));
    }
    }
    int ans=min(min(f[n][0],f[n][1]),min(f[n][2],f[n][3]));
    if(ans>10000000)cout<<"-1\n";
    else cout<<ans<<'\n';
    // cout<<)<<'\n';
}