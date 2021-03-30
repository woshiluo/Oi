#include <stdio.h>

int n,v;
int a[31],f[210000];

int main(){
    scanf("%d%d",&v,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
    for(int i=1;i<=n;i++){
        for(int j=v;j>=a[i];j--){
            if(f[j-a[i]]+a[i]>f[j]) f[j]=f[j-a[i]]+a[i];
        }
    }
    printf("%d",v-f[v]);
}
