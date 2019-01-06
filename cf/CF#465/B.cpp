#include <cstdio>
using namespace std;

int n,x,y,cnt;
char next;

int main(){
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
        char temp;
        scanf("%c",&temp);
        if(next!=0){
            if(temp==next) cnt++;
            next=0;
        }
        if(temp=='R') x++;
        if(temp=='U') y++;
        if(x==y){ next=temp;}
    }
    printf("%d",cnt);
}
