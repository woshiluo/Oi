#include <cstdio>
using namespace std;

int n,k;
int a[1100];

int find(int l,int h,int k){
    int mid;
    while(l<=h){
        mid=(l+h)/2;
        if(a[mid]>k) h=mid-1;
        else if(a[mid]<k) l=mid+1;
        else return mid;
    }
    return -2;
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<=n-1;i++) scanf("%d",&a[i]);
    scanf("%d",&k);
    int left=0,right=n-1;
    printf("%d",find(left,right,k)+1);
    return 0;
}
