#include <cstdio>
#include <algorithm>
using namespace std;

int n,r,q;
struct node {
    int n,s,p;
}a[210000],left[110000],right[110000];

int lcnt,rcnt,cnt,result_start;

bool cmp(node a,node b){
    if(a.s==b.s) return a.n<b.n;
    else return a.s>b.s;
}

void marge(int left_start,int right_start){
    result_start=1;
    while(left_start<=n&&right_start<=n){
        if(cmp(left[left_start],right[right_start])) a[result_start++]=left[left_start++];
        else a[result_start++]=right[right_start++];
    }
    while(left_start<=n) a[result_start++]=left[left_start++];
    while(right_start<=n) a[result_start++]=right[right_start++];
}

int main(){
    scanf("%d%d%d",&n,&r,&q);

    for(int i=1;i<=2*n;i++){scanf("%d",&a[i].s);a[i].n=i;}
    for(int i=1;i<=2*n;i++) scanf("%d",&a[i].p);

/*  for(int i=1;i<=2*n;i++){
        printf("%d ",a[i].s);
    }
    printf("\n");   */
 sort(a+1,a+1+2*n,cmp);
    for(int i=1;i<=r;i++){
        lcnt=rcnt=0;
        for(int j=1;j<=2*n;j+=2){
            if(a[j].p>=a[j+1].p){
                a[j].s+=1;
                //printf("%d\n",++cnt);
                left[++lcnt]=a[j];right[++rcnt]=a[j+1];
            }
            else{
                a[j+1].s+=1;
                //printf("%d\n",++cnt);
                right[++rcnt]=a[j];left[++lcnt]=a[j+1];
            }
        }
        if(i==1) sort(a+1,a+1+2*n,cmp);
        else marge(1,1);
/*        for(int i=1;i<=2*n;i++) printf("%d ",a[i].s);
        printf("\n");
        for(int i=1;i<=2*n;i++) printf("%d ",a[i].n);
        printf("\n");*/
    }

    printf("%d",a[q].n);
}
