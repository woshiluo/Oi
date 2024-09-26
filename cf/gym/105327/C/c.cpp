#include<bits/stdc++.h>
using namespace std;
int Len,m,str[100010],st[100010],rk[100010],tp[100010],sa[100010],height[100010];
void radix_sort()
{
    for(int i=0;i<=m;st[i++]=0);
    for(int i=1;i<=Len;st[rk[i++]]++);
    for(int i=1;i<=m;i++)st[i]+=st[i-1];
    for(int i=Len;i;i--)sa[st[rk[tp[i]]]--]=tp[i];
}
void suffix_sort()
{
    for(int i=1;i<=Len;i++)
        rk[i]=str[i],tp[i]=i;
    radix_sort();
    for(int k=1,p=0;p<Len;m=p,k<<=1){
        p=0;
        for(int i=1;i<=k;i++)tp[++p]=Len-k+i;
        for(int i=1;i<=Len;i++)
        if(sa[i]>k)tp[++p]=sa[i]-k;
        radix_sort();
        memcpy(tp,rk,sizeof tp);
        rk[sa[1]]=p=1;
        for(int i=2;i<=Len;i++)
            rk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;
    }
}
void get_H()
{
    for(int i=1,j=0,k=0;i<=Len;i++){
        if(rk[i]==1)continue;
        if(k)k--;
        j=sa[rk[i]-1];
        while(i+k<=Len&&j+k<=Len&&str[i+k]==str[j+k])k++;
        height[rk[i]]=k;
    }
}
int main()
{
    scanf("%d",&Len);m=Len;
    for(int i=1;i<=Len;i++)
        scanf("%d",&str[i]);
    suffix_sort();
    get_H();
    // for(int i=1;i<=Len;i++){
    //     cout<<height[i]<<'\n';
    // }
    long long fz=0,fm=1ll*Len*Len,gg,temp=0;
    int top=0;
    memset(st,0,sizeof st);
    st[0]=1;
    for(int i=2;i<=Len;i++){
        while(top&&height[i]<height[st[top]]){
            temp-=1ll*(st[top]-st[top-1])*height[st[top]];
            // cout<<"SUB "<<(st[top]-st[top-1])<<' '<<height[rk[st[top]]]<<endl;
            temp+=1ll*(st[top]-st[top-1])*height[i];
            // cout<<"ADD "<<(st[top]-st[top-1])<<' '<<height[rk[i]]<<endl;
            top--;
        }
        st[++top]=i;
        temp+=height[i];
        fz+=temp;
        // cout<<i<<','<<temp<<'\n';
    }
    fz=fz*2+1ll*Len*(Len+1)/2;
    // cout<<fz<<' '<<fm?<<'\n';
    gg=__gcd(fz,fm);
    cout<<fz/gg<<'/'<<fm/gg<<'\n';
}