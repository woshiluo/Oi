#include <cstdio>
using namespace std;

int V,n;
int a[110],f[110];
int main(){
    scanf("%d%d",&V,&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        for(int j=V;j>=a[i];j--){
            if(f[j-a[i]]+a[i]>f[j]) 
                f[j]=f[j-a[i]]+a[i];
        }
    }
    printf("%d",V-f[V]);
}
