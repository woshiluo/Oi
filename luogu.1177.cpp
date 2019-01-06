#include <cstdio>
using namespace std;

int n;
int result[110000];
int a[110000];

void marge(int *data,int start,int end,int *result){
    int left_start,result_start,right_start;
    left_start=result_start=start;
    right_start=(start+end+1)/2+1;

    while(left_start<=(start+end+1)/2&&right_start<=end){
        if(data[left_start]<data[right_start]) result[result_start++]=data[left_start++];
        else result[result_start++]=data[right_start++];
    }

    while(left_start<=(start+end+1)/2) result[result_start++]=data[left_start++];
    while(right_start<=end) result[result_start++]=data[right_start++];
} 

void margesort(int *data,int start,int end,int *result){
    if(end-start==1){
        if(data[start]>data[end]){
            int temp=data[end];
            data[end]=data[start];
            data[start]=temp;
        }   
        return ;
    }
    else if(end-start==0) return ;
    else {
        margesort(data,start,(start+end+1)/2,result);
        margesort(data,(start+end+1)/2+1,end,result);

        marge(data,start,end,result);

        for(int i=start;i<=end;i++) data[i]=result[i];
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);

    margesort(a,1,n,result);

    for(int i=1;i<=n;i++) printf("%d ",a[i]);
}
