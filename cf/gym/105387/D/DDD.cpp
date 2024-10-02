#include<bits/stdc++.h>
using namespace std;
char str[210010];
int Len,ans=0,d[210010],Lp,Rp;
int check(int i,int j)
{
    if(str[i]=='A'&&str[j]=='T')return 1;
    if(str[i]=='T'&&str[j]=='A')return 1;
    if(str[i]=='C'&&str[j]=='G')return 1;
    if(str[i]=='G'&&str[j]=='C')return 1;
    return 0;
}
int check2(int l,int r)
{
    for(int i=0;i<r-l;i++)
    if(!check(l+i,r-i))
        return 0;
    return 1;
}
int main()
{
#ifdef woshiluo 
	freopen( "d.in", "r", stdin );
	freopen( "d.ans", "w", stdout );
#endif
    scanf("%s",str+1);
    Len=strlen(str+1);
    for(int l=1;l<=Len;l++)
    for(int r=l+1;r<=Len;r+=2)
    if(check2(l,r)){
        ans=max(ans,r-l+1);
        // cout<<l<<' '<<r<<'\n';
    }
    cout<<ans<<'\n';
}
