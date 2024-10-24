#include<bits/stdc++.h>
#define LL long long
using namespace std;
int tot1[30],tot2[30],Len1,Len2,need[30];
char s1[2000010],s2[2000010];
inline int read()
{
    int x=0;char ch=0,w=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int calc(int cnt)
{
    for(int i=0;i<26;i++){
        if(!tot2[i])continue;
        int R=tot2[i]/cnt,L=(tot2[i]+cnt)/(cnt+1);
        if(L>R)return -1e9;
        need[i]=L;
    }
    int temp=1e9,flag=1,weiba=0;
    for(int i=0;i<26;i++)
    if(tot2[i]){
        temp=min(temp,tot1[i]/need[i]);
        if(need[i]*cnt<tot2[i])
            weiba=1;
    }
    if(temp<cnt)
        return -1e9;
    for(int i=0;i<26;i++)
    if(tot2[i]){
        if(tot1[i]-need[i]*temp<tot2[i]-need[i]*cnt)
            flag=0;
    }
    return (temp-cnt+1-weiba)+flag*weiba;
}
int main()
{
    int T=read();
    while(T --> 0){
        scanf("%s%s",s1+1,s2+1);
        for(int i=0;i<26;i++)
            tot1[i]=tot2[i]=0;
        Len1=strlen(s1+1);
        Len2=strlen(s2+1);
        for(int i=1;i<=Len1;i++)
            tot1[s1[i]-'a']++;
        for(int i=1;i<=Len2;i++)
            tot2[s2[i]-'a']++;
        int Min=1e9,temp=1e9;
        for(int i=0;i<26;i++)
        if(tot2[i])Min=min(tot2[i],Min),temp=min(temp,tot1[i]/tot2[i]);
        for(int i=1;i<=Min;i++)
            temp=max(temp,calc(i));
        printf("%d\n",temp);
    }
}
/*
1
aaaabbbbbbcccccccc
aaabbbbbcccccc


2
bajkaaall aal
abca cba
*/