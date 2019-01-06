#include <cstdio>
using namespace std;

int x,y;

int main(){
    scanf("%d%d",&x,&y);
    if(x==0){
        printf("No"); 
        return 0;
    }
    x=x-y+1;
    if(x%2==0&&x>=0) printf("Yes");
    else printf("No");
}
