#include <cstdio>
using namespace std;

int n;
int a[110000];

void qsort(int *data,int s,int e){
    int o_l=s,o_r=e;
    int base=data[(s+e)/2];
    do{
        while(data[s]<base) s++;
        while(data[e]>base) e--;
        if(s<=e){
            int temp=data[s];
            data[s]=data[e];
            data[e]=temp;
            s++;
            e--;
        }
    }while(s<=e);
    if(o_l<e) qsort(data,o_l,e);
    if(s<o_r) qsort(data,s,o_r);
    
} 

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    qsort(a,1,n);

    for(int i=1;i<=n;i++) printf("%d ",a[i]);
}
