#include <cstdio>
#include <cstring>
using namespace std;

struct node {
    char x;
    int next;
}a[110000];

int now,len,head,last;

int main(){
    char temp;
    last=head=0;
    a[head].next=last;
    now=head;
    while(scanf("%c",&temp)!=EOF){
        if(temp=='[') now=0;
        else if(temp==']') now=last;
        else if(temp=='\n') {
            for(int i=a[head].next;;i=a[i].next){
                printf("%c",a[i].x);
                if(i==last) break;
            }
            printf("\n");
            memset(a,0,sizeof(a));
            now=0;
            len=0;
            last=0;
        }
        else {
            len++;
            if(last==now) last=len;
            a[len].x=temp;
            a[len].next=a[now].next;
            a[now].next=len;
            now=len;
        }
    }
    
}
