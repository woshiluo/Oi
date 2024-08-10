#include<bits/stdc++.h>
#define LL long long
using namespace std;
int Len;
char S[1000010];
inline int read()
{
    int x=0,w=0;char ch=0;
    while(!isdigit(ch)){w|=ch=='-';ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return w?-x:x;
}
int check()
{
    int top=0;
    for(int i=1;i<=Len;i++){
        if(top==0){
            if(S[i]!='a')return 0;
            top++;
        }else if(top==1){
            if(S[i]!='v')return 0;
            top++;
        }else if(top==2){
            if(S[i]!='a')return 0;
            top++;
        }else if(top==3){
            if(S[i]!='a'&&S[i]!='v')
                return 0;
            if(S[i]=='a')top=1;
            else top++;
        }else if(top==4){
            if(S[i]!='a')return 0;
            top=0;
        }
        //cout<<i<<' '<<top<<'\n';
    }
    return top==0||top==3;
}
int main()
{
    int T=read();
    while(T --> 0){
        scanf("%s",S+1);
        Len=strlen(S+1);
        printf(check()?"Yes\n":"No\n");
    }
}
/*
9 2
abcabacba
be
*/