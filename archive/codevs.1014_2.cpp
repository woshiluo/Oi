#include <stdio.h>

int n,v;
int a[40],f[40][210000];

int main(){
    scanf("%d%d",&v,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
    for(int i=1;i<=n;i++){
        for(int j=v;j>=a[i];j--){
            if(f[i-1][j-a[i]]+a[i]>f[i-1][j]) f[i][j]=f[i-1][j-a[i]]+a[i];
            else f[i][j]=f[i-1][j];
        }
        for(int j=1;j<a[i];j++) f[i][j]=f[i-1][j];
    }
    printf("%d",v-f[n][v]);
}
