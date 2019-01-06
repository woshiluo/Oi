#include <cstdio>

int w,h;
int u1,u2,d1,d2;

int main(){
    scanf("%d%d%d%d%d%d",&w,&h,&u1,&d1,&u2,&d2);
    while(h){
        w+=h;
        if(h==d1) w-=u1;
        if(h==d2) w-=u2;
        if(w<0) w=0;
        h--;
    }  
    printf("%d",w);
}
