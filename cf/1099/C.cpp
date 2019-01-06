#include <cstdio>
#include <cstring>

int k,len,zlen,sfcnt,tmp;
bool sf,cd;
char s[1000];

int main(){
    scanf("%s",s+1);
    scanf("%d",&k);
    len=strlen(s+1);
    for(int i=1;i<=len;i++){
        if(s[i]>='a'&&s[i]<='z') 
            zlen++;
        if(s[i]=='?') sfcnt++;
        if(s[i]=='*') {cd=true;sfcnt++;}
    }
    if(zlen>k){
        if(sfcnt<zlen-k){
            printf("Impossible");
            return 0;
        } 
        for(int i=1;i<=len;i++){
            if(s[i]=='*'||s[i]=='?') continue;
            if(s[i+1]=='?'||s[i+1]=='*'){
                if(zlen>k) {zlen--;sfcnt--;}   
                else printf("%c",s[i]);
            } 
            else printf("%c",s[i]);
        }
    } 
    else if(zlen==k){
        for(int i=1;i<=len;i++){
            if(s[i]=='*'||s[i]=='?') continue;
            else printf("%c",s[i]);
        }
    }
    else if(zlen<k){
        if(!cd){
            printf("Impossible");
            return 0;
        }
        for(int i=1;i<=len;i++){
            if(s[i]=='*'||s[i]=='?') continue;
            else if(s[i+1]=='*'){
                printf("%c",s[i]);
                while(1){
                   if(zlen>=k) break;
                   printf("%c",s[i]);
                   zlen++;
                } 
            }
            else printf("%c",s[i]);
        } 
    }
}
