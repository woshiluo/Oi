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
int main()
{
    scanf("%s",str+1);
    Len=strlen(str+1);
    // for(int i=1,l=1,r=1,k=1;i<=Len;i++){
    //     k=i<r?min(r-i,d[l+r-i]):1;
    //     while(i>k&&i+k<=Len&&check(i-k,i+k))k++;
    //     d[i]=--k;
    //     if(i+k>r)r=i+k,l=i-k;
    //     ans=max(ans,d[i]*2+1);
    //     if(ans==d[i]*2+1)
    //         Lp=i-d[i],Rp=i+d[i];
    // }
    for(int i=1,l=1,r=0,k=1;i<=Len;i++){
        k=i<r?min(r-i,d[l+r-i-1]):0;
        while(i>=k&&i+k<=Len&&check(i-k+1,i+k))k++;
        d[i]=--k;
        if(i+k>r)r=i+k,l=i-k+1;
        ans=max(ans,d[i]*2);
        if(ans==d[i]*2)
            Lp=i-d[i]+1,Rp=i+d[i];
    }
    cout<<ans<<'\n';
    for(int i=Lp;i<=Rp;i++)
        printf("%c",str[i]);
    cout<<endl;
}