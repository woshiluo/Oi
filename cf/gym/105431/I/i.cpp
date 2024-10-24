#include<bits/stdc++.h>
using namespace std;
int LenS,LenD,LenM;
int a[2010],cnt;
char s[2010],d[2010],m[2010];
void print(long long x)
{
    if(!x)return;
    print(x/2);
    printf("%lld",x%2);
}
void solve()
{
    for(int i=1;i<=LenM;i++)
        a[i]=m[i]-'0';
    int DDD=0;
    cnt=LenM;
    if(LenD<21){
        for(int i=1;i<=LenD;i++)
            DDD=DDD*2+d[i]-'0';
    }else DDD=1e9;

    for(int i=1;;i++){
        if(cnt<DDD){
            print((i-1)*DDD+cnt);
            exit(0);
        }
        for(int j=1;j<=cnt;j++){
            if(j+DDD<=cnt)a[j]=a[j+DDD];
            else a[j]=0;
        }
        cnt-=DDD;
        for(int j=1;j<=max(cnt,LenS);j++){
            if(j<=LenS)
                a[j]+=s[j]-'0';
            a[j+1]+=a[j]/2;
            a[j]%=2;
        }
        cnt=max(cnt,LenS);
        while(a[cnt+1]){
            cnt++;
            a[cnt+1]+=a[cnt]/2;
            a[cnt]%=2;
        }
        if(LenS>=DDD){
            printf("Infinite money!\n");
            exit(0);
        }
    }
}
int main()
{
    scanf("%s",s+1);
    scanf("%s",d+1);
    scanf("%s",m+1);
    LenS=strlen(s+1);
    LenD=strlen(d+1);
    LenM=strlen(m+1);
    reverse(s+1,s+1+LenS);
    reverse(m+1,m+1+LenM);
    solve();
}

/*

101110101
1010
10001110101010101


*/