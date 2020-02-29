#include <cstdio>
#include <cstring>
using namespace std;

char s[110000];
char a[1100],b[1100];
int alen,blen,slen;
bool flag;
int lx;
//lx 1 - 小数
//   2 - 分数
//   3 - 百分数

int main(){
    scanf("%s",s);
    slen=strlen(s);

    for(int i=0;i<slen;i++){
        if(!flag){
            if(s[i]=='.') lx=1,flag=true;
            else if(s[i]=='/') lx=2,flag=true;
            else if(s[i]=='%') lx=3,flag=true;
            else a[alen++]=s[i];
        }
        else b[blen++]=s[i];
    }

    bool x=false;
    
    for(int i=alen-1;i>=0;i--){
        if(!x&&a[i]=='0') continue;
        else {
            x=true;
            printf("%c",a[i]);
        }
    }
    if(!x&&a[0]=='0') printf("0");
    
    if(lx==3) printf("%%");
    if(!flag) return 0;
    else {
        if(lx==1) printf(".");
        if(lx==2) printf("/");
    }
    x=false;
    int temp=0;
    if(lx==1) while(b[temp]=='0'){temp++;};  
    for(int i=blen-1;i>=temp;i--){
        if(lx!=1){
            if((!x)&&b[i]=='0') {continue;}
        }
        x=true;
        printf("%c",b[i]);
    }
    if(!x&&b[0]=='0') printf("0"); 
}
