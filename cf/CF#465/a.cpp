#include <cstdio>
#include <cmath>
using namespace std;

int n;
int a[100000],alen=1;
bool x[100000];


bool zs(int s){
    for(int i=2;i<alen;i++){
        if(s%a[i]==0) return false;
    }
    return true;
}

void zsb(int b){
    for(int i=3;i<=b;i++){
        if(zs(b)) a[alen++]=i;
    }
} 

int main(){
    a[0]=2;
    scanf("%d",&n);
    zsb(sqrt(n));
    for(int i=0;i<alen;i++) printf("%d ",a[i]);
}
