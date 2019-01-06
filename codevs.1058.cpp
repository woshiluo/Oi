#include <cstdio>
using namespace std;

int n,k;

struct node {
    int a,left,rig;
}a[2110000];

int b[2110000];
int main(){
    int max;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) scanf("%d",&a[i].a);
    for(int i=1;i<=k;i++){
        max=0;
        for(int j=1;j<i;j++){
            if(a[j].a<a[i].a&&a[j].left+1>max){
                max=a[j].left+1;
            }
        }
        a[i].left=max;
    }
    for(int i=n;i>=k;i--){
        max=0;
        for(int j=n;j>i;j--){
            if(a[j].a>a[i].a&&a[j].rig+1>max){
                max=a[j].rig+1;
            }
        }
        a[i].rig=max;
    }
    max=0;
    if(a[k].left+a[k].rig+1>max) max=a[k].left+a[k].rig+1; 
    printf("%d",max);
}
