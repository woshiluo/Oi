#include <cstdio>
using namespace std;

int n;
struct node {
    int a,b,x,y;
}a[11000];

int main(){
    scanf("%d",&n);
    int cnt=0;
    for(int i=1;i<=n;i++) {
        int d,b,x,y;
        cnt++;
        scanf("%d%d%d%d",&a[cnt].a,&a[cnt].b,&a[cnt].x,&a[cnt].y);
    }
    int x,y;
    scanf("%d%d",&x,&y);
    int temp=-1;
    for(int i=1;i<=n;i++){
        if(x>=a[i].a&&x<=a[i].a+a[i].x&&y>=a[i].b&&y<=a[i].b+a[i].y){
            temp=i;
        }
    }
    printf("%d",temp);
}
