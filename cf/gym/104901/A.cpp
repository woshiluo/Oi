#include<bits/stdc++.h>
using namespace std;
int Len,tot,flag,top;
char str[1000010],*s,st[1000010];
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    int T;cin>>T;
    s=str+1;
    while(T --> 0){
        // cin>>s;
        scanf("%s",str+1);
        Len=strlen(str+1);
        tot=flag=top=0;
        for(int i=1;i<=Len;i++){
            if(!top){
                tot++;
                if(str[i]=='('||str[i]==')')
                    st[++top]=1;
                else st[++top]=2;
            }else{
                char temp=0;
                if(str[i]=='('||str[i]==')')
                    temp=1;
                else temp=2;
                if(st[top]!=temp)
                    st[++top]=temp;
                else{
                    for(int j=1;j<=top;j++)
                    if(i+j-1<=Len){
                        char temp2=0;
                        if(str[i+j-1]=='('||str[i+j-1]==')')
                            temp2=1;
                        else temp2=2;
                        if(temp2!=st[top-j+1])
                            tot=10;
                    }else tot=10;
                    if(i+top<=Len){
                        if((str[i+top]=='('||str[i+top]==')')==(str[i+top-1]=='('||str[i+top-1]==')'))
                            flag=1;
                    }
                    i+=top-1;
                    top=0;
                }
            }
        }
        // cout<<tot<<' '<<flag<<'\n';
        if(tot<3&&!flag)
            printf("Yes\n");
        else printf("No\n");
    }
}